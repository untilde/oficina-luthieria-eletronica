<script setup lang="ts">
import { onMounted, onBeforeUnmount, ref } from 'vue'
import { scaleLog, type ScaleLogarithmic } from 'd3-scale'
import { axisBottom } from 'd3-axis'
import { select } from 'd3-selection'

const props = withDefaults(
  defineProps<{
    analyser?: AnalyserNode | null
    barColor?: string
    width?: number
    height?: number
  }>(),
  { height: 200 },
)

const canvasRef = ref<HTMLCanvasElement | null>(null)
const axisRef = ref<SVGGElement | null>(null)
let raf = 0
let ro: ResizeObserver | null = null
const AXIS_HEIGHT = 34

onMounted(() => {
  const canvas = canvasRef.value!
  const ctx = canvas.getContext('2d')!
  const analyser = props.analyser
  if (!analyser) return

  const bufferLen = analyser.frequencyBinCount
  const buffer = new Uint8Array(bufferLen)

  const minFreq = 20
  const maxFreq = 22050

  // Convert frequency index -> frequency (Hz)
  const indexToFreq = (i: number) => (i * analyser.context.sampleRate) / (2 * bufferLen)

  // Map log frequency (20–22050 Hz) to X pixel coordinate
  const freqToX = (f: number) => {
    const minLog = Math.log10(minFreq)
    const maxLog = Math.log10(maxFreq)
    return ((Math.log10(f) - minLog) / (maxLog - minLog)) * canvas.width
  }

  const ticks = [20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000]
  const scale: ScaleLogarithmic<number, number> = scaleLog().domain([minFreq, maxFreq]).clamp(true)
  function renderAxis() {
    if (!axisRef.value) return
    scale.range([0, canvas.width])
    const ax = axisBottom(scale)
      .tickValues(ticks)
      .tickSize(3)
      .tickFormat((d: any) => {
        const v = Number(d)
        if (v >= 1000) return v % 1000 === 0 ? v / 1000 + 'k' : (v / 1000).toFixed(1) + 'k'
        return String(v)
      })
    const g = select(axisRef.value)
    g.call(ax as any)
    g.selectAll('text').attr('fill', '#94a3b8').attr('font-size', 10)
  }

  // Keep axis in sync with canvas size
  ro = new ResizeObserver(() => renderAxis())
  ro.observe(canvas)
  renderAxis()

  const draw = () => {
    const { width, height } = canvas
    ctx.clearRect(0, 0, width, height)
    ctx.fillStyle = props.barColor ?? '#34d399'

    analyser.getByteFrequencyData(buffer)

    const step = Math.max(1, Math.floor(bufferLen / 200)) // ~200 bars max
    const smooth = 3 // moving average window

    for (let i = 0; i < bufferLen; i += step) {
      const freq = indexToFreq(i)
      if (freq < minFreq || freq > maxFreq) continue

      // Average a few nearby bins for smoother display
      let sum = 0
      for (let j = 0; j < smooth; j++) sum += buffer[Math.min(i + j, bufferLen - 1)] ?? 0
      const value = sum / smooth

      const v = value / 255
      const barHeight = v * height * 0.9
      const x = freqToX(freq)
      const barWidth = 2.5 // constant width

      ctx.fillRect(x, height - barHeight, barWidth, barHeight)
    }

    raf = requestAnimationFrame(draw)
  }

  draw()
})

onBeforeUnmount(() => {
  cancelAnimationFrame(raf)
  ro?.disconnect()
  ro = null
})
</script>

<template>
  <div>
    <canvas
      ref="canvasRef"
      class="block rounded bg-slate-900"
      :width="props.width ?? 700"
      :height="props.height ?? 200"
    />
    <svg :width="props.width ?? 700" :height="AXIS_HEIGHT" class="block mt-1">
      <g class="axis" ref="axisRef" :transform="`translate(0, ${AXIS_HEIGHT - 14})`" />
    </svg>
  </div>
</template>

<style scoped></style>
