<script setup lang="ts">
import { onMounted, onBeforeUnmount, ref, watch } from 'vue'
const props = withDefaults(
  defineProps<{
    analyser?: AnalyserNode | null
    lineColor?: string
    width?: number
    height?: number
  }>(),
  { height: 200 },
)
const canvasRef = ref<HTMLCanvasElement | null>(null)
let raf = 0

onMounted(() => {
  const canvas = canvasRef.value!
  const ctx2d = canvas.getContext('2d')!
  const buffer = new Uint8Array((props.analyser?.fftSize ?? 2048) as number)

  const draw = () => {
    const { width, height } = canvas
    ctx2d.clearRect(0, 0, width, height)
    // midline axis
    ctx2d.strokeStyle = '#475569' // slate-600
    ctx2d.lineWidth = 1
    ctx2d.beginPath()
    ctx2d.moveTo(0, height / 2)
    ctx2d.lineTo(width, height / 2)
    ctx2d.stroke()

    if (props.analyser) {
      props.analyser.getByteTimeDomainData(buffer)
      ctx2d.strokeStyle = props.lineColor ?? '#60a5fa'
      ctx2d.lineWidth = 2
      ctx2d.beginPath()
      const len = buffer.length
      for (let i = 0; i < len; i++) {
        const x = (i / (buffer.length - 1)) * width
        const v = ((buffer[i] ?? 128) - 128) / 128
        const y = height / 2 + v * (height / 2 - 4)
        if (i === 0) ctx2d.moveTo(x, y)
        else ctx2d.lineTo(x, y)
      }
      ctx2d.stroke()
    }
    raf = requestAnimationFrame(draw)
  }
  draw()
})

onBeforeUnmount(() => cancelAnimationFrame(raf))

watch(
  () => props.analyser,
  () => {
    // no-op; draw loop reads current analyser
  },
)
</script>

<template>
  <canvas
    ref="canvasRef"
    class="block rounded bg-slate-900"
    :width="props.width ?? 600"
    :height="props.height ?? 200"
  />
</template>

<style scoped></style>
