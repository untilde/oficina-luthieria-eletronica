export function useAudioContext() {
  let ctx = (window as any)._globalAudioCtx as AudioContext | undefined
  if (!ctx) {
    const AC = (window.AudioContext || (window as any).webkitAudioContext) as typeof AudioContext
    ctx = new AC()
    ;(window as any)._globalAudioCtx = ctx
  }
  return ctx!
}
