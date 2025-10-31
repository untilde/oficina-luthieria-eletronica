import { ref, onBeforeUnmount } from 'vue'
import { useAudioContext } from './useAudioContext'

export function useOscillator(options?: {
  type?: OscillatorType
  initialFreq?: number
  connectAnalyser?: boolean
}) {
  const ctx = useAudioContext()
  const isRunning = ref(false)
  const frequency = ref(options?.initialFreq ?? 440)
  const type = ref<OscillatorType>(options?.type ?? 'sine')

  let osc: OscillatorNode | null = null
  const gain = new GainNode(ctx, { gain: 0 }) // initially muted
  let analyser: AnalyserNode | null = null

  if (options?.connectAnalyser) {
    analyser = new AnalyserNode(ctx, { fftSize: 2048, smoothingTimeConstant: 0.8 })
    gain.connect(analyser)
    analyser.connect(ctx.destination)
  } else {
    gain.connect(ctx.destination)
  }

  function ensureOsc() {
    if (!osc) {
      osc = new OscillatorNode(ctx, { type: type.value, frequency: frequency.value })
      osc.connect(gain)
      try {
        osc.start()
      } catch {
        /* already started */
      }
    }
  }

  function start() {
    if (ctx.state === 'suspended') ctx.resume()
    ensureOsc()
    gain.gain.linearRampToValueAtTime(0.2, ctx.currentTime + 0.03)
    isRunning.value = true
  }
  function stop() {
    gain.gain.linearRampToValueAtTime(0.0, ctx.currentTime + 0.05)
    isRunning.value = false
  }
  function setFrequency(hz: number) {
    frequency.value = hz
    ensureOsc()
    if (osc) osc.frequency.setTargetAtTime(hz, ctx.currentTime, 0.01)
  }
  function setType(t: OscillatorType) {
    type.value = t
    ensureOsc()
    if (osc) osc.type = t
  }

  onBeforeUnmount(() => {
    try {
      gain.disconnect()
      analyser?.disconnect()
      osc?.disconnect()
      osc?.stop()
    } catch {
      /* noop */
    }
    osc = null
  })

  return { isRunning, frequency, type, start, stop, setFrequency, setType, analyser }
}
