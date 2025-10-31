<script setup lang="ts">
import { ref, onMounted, onBeforeUnmount, watch } from 'vue'

const width = 695
const height = 205

const speed = ref(12) // corresponds to frequency slider (4..20)
const intensity = ref(25) // amplitude percent (0..100)
const canvasRef = ref<HTMLCanvasElement | null>(null)
let raf = 0

function amp() {
  return (intensity.value / 100) * 0.5 // scale to 0..0.5 like original
}
function freq() {
  return speed.value / 100 // scale like original updateSpeed(freq)
}

onMounted(() => {
  const canvas = canvasRef.value!
  const ctx = canvas.getContext('2d')!
  const particles = 60
  const cols = particles
  const rows = 3
  let t = 0

  function draw() {
    const w = canvas.width
    const h = canvas.height
    ctx.clearRect(0, 0, w, h)

    // Draw "particles" as circles whose density is modulated by a sine wave
    const A = amp()
    const F = freq()

    const left = 20
    const right = w - 20
    const top = 20
    const bottom = h - 80

    // Grid of dots
    for (let r = 0; r < rows; r++) {
      for (let c = 0; c < cols; c++) {
        const x = left + (c / (cols - 1)) * (right - left)
        const y = top + r * ((bottom - top) / (rows - 1))
        // wave phase travels to the right over time
        const v = Math.sin((x * F + t) * 2 * Math.PI)
        const density = 0.5 + (v * A) / 2
        const alpha = 0.35 + 0.65 * density
        ctx.fillStyle = `rgba(148,163,184,${alpha.toFixed(3)})` // slate-400 varying alpha
        ctx.beginPath()
        ctx.arc(x, y, 2, 0, Math.PI * 2)
        ctx.fill()
      }
    }

    // Center the waveform vertically on the canvas
    const waveTop = 20
    const waveBottom = h - 20
    const baseY = h / 2
    // axis baseline
    ctx.strokeStyle = '#64748b' // slate-500
    ctx.lineWidth = 1
    ctx.beginPath()
    ctx.moveTo(0, baseY)
    ctx.lineTo(w, baseY)
    ctx.stroke()

    // wave
    ctx.strokeStyle = '#94a3b8' // slate-400
    ctx.lineWidth = 2
    ctx.beginPath()
    const maxAmp = (waveBottom - waveTop) / 2 - 2
    for (let i = 0; i < w; i++) {
      const v = Math.sin((i / w + t) * 2 * Math.PI * (F * 8))
      const y = baseY - v * maxAmp * (A / 0.5)
      if (i === 0) ctx.moveTo(i, y)
      else ctx.lineTo(i, y)
    }
    ctx.stroke()

    t += 0.01 + F * 0.5
    raf = requestAnimationFrame(draw)
  }
  draw()
})

onBeforeUnmount(() => cancelAnimationFrame(raf))

watch([speed, intensity], () => {
  // reactive redraw handled in loop using latest values
})
</script>

<template>
  <div class="w-full relative">
    <canvas ref="canvasRef" :width="695" :height="205" class="w-full rounded bg-slate-900" />
    <div class="grid grid-cols-1 md:grid-cols-2 gap-4 mt-3 relative z-10">
      <div class="text-center pointer-events-auto">
        <label class="block text-sm text-slate-400">Frequência</label>
        <input type="range" min="4" max="20" step="1" v-model.number="speed" />
      </div>
      <div class="text-center pointer-events-auto">
        <label class="block text-sm text-slate-400">Amplitude</label>
        <input type="range" min="0" max="100" step="1" v-model.number="intensity" />
      </div>
    </div>
  </div>
</template>

<style scoped></style>
