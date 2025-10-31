<script setup lang="ts">
import { ref, computed, onMounted, onBeforeUnmount, watch } from 'vue'
import { useOscillator } from '@/composables/useOscillator'
import Oscilloscope from './Oscilloscope.vue'
import Spectrum from './Spectrum.vue'
import { scaleLog, type ScaleLogarithmic } from 'd3-scale'

// Log scale from 20 Hz to 8000 Hz
const MIN = 20
const MAX = 8000

const xScale = ref<ScaleLogarithmic<number, number> | null>(null)
const measuredWidth = ref(600)
const PLOT_WIDTH = computed(() => measuredWidth.value)
// Axis is rendered inside Spectrum component; no local axis here.

function updateScale() {
  xScale.value = scaleLog().domain([MIN, MAX]).range([0, PLOT_WIDTH.value]).clamp(true)
}
function hzToX(hz: number): number {
  return (xScale.value?.(hz) as number) ?? 0
}
function xToHz(x: number) {
  return xScale.value?.invert ? (xScale.value.invert(x) as number) : MIN
}

const { analyser, isRunning, frequency, start, stop, setFrequency } = useOscillator({
  initialFreq: 440,
  connectAnalyser: true,
})

const container = ref<HTMLDivElement | null>(null)
const dragging = ref<boolean>(false)
const displayFreq = computed(() => `${Math.round(frequency.value)} Hz`)

function onPointerDown(e: PointerEvent) {
  dragging.value = true
  ;(e.target as Element).setPointerCapture?.(e.pointerId)
  updateFromEvent(e)
}
function onPointerMove(e: PointerEvent) {
  if (!dragging.value) return
  updateFromEvent(e)
}
function onPointerUp(e: PointerEvent) {
  dragging.value = false
  ;(e.target as Element).releasePointerCapture?.(e.pointerId)
}
function updateFromEvent(e: PointerEvent) {
  const el = container.value!
  const rect = el.getBoundingClientRect()
  const x = e.clientX - rect.left
  const hz = xToHz(x)
  setFrequency(hz)
}

onMounted(() => {
  // Observe width changes to keep the scale in sync
  const ro = new ResizeObserver((entries) => {
    for (const entry of entries) {
      if (entry.contentRect) {
        measuredWidth.value = Math.max(200, Math.floor(entry.contentRect.width))
        updateScale()
      }
    }
  })
  if (container.value) ro.observe(container.value)
  updateScale()
  ;(container as any)._ro = ro
})

onBeforeUnmount(() => {
  const ro: ResizeObserver | undefined = (container as any)?._ro
  ro?.disconnect()
})

// no local axis to render
</script>

<template>
  <div class="w-full max-w-3xl mx-auto">
    <div class="flex items-center justify-between mb-2">
      <div class="text-sm text-slate-400">Clique e arraste para mudar a frequência</div>
      <div class="text-sm text-slate-300">{{ displayFreq }}</div>
    </div>
    <div
      ref="container"
      class="relative w-full select-none"
      @pointerdown.prevent="onPointerDown"
      @pointermove.prevent="onPointerMove"
      @pointerup.prevent="onPointerUp"
    >
      <Oscilloscope :analyser="analyser ?? undefined" :width="PLOT_WIDTH" />
      <Spectrum class="mt-2" :analyser="analyser ?? undefined" :width="PLOT_WIDTH" />
      <div class="absolute inset-x-0" :style="{ top: 0, bottom: '0px' }">
        <!-- Frequency marker overlay across plots -->
        <div
          class="absolute top-0 bottom-0 border-l border-white/40"
          :style="{ left: Number(hzToX(frequency)) + 'px' }"
        />
      </div>
    </div>
    <div class="flex items-center justify-center gap-3 mt-3">
      <button
        type="button"
        class="px-3 py-1.5 rounded bg-blue-600 hover:bg-blue-500 text-white text-sm"
        v-if="!isRunning"
        @click="start"
      >
        Play
      </button>
      <button
        type="button"
        class="px-3 py-1.5 rounded bg-slate-700 hover:bg-slate-600 text-white text-sm"
        v-else
        @click="stop"
      >
        Stop
      </button>
    </div>
  </div>
</template>

<style scoped></style>
