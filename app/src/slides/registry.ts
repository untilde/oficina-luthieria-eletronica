import type { Component } from 'vue'

// Auto-discover all slide components under this folder
const modules = import.meta.glob('./**/*.vue', { eager: true })

// Optional manual section name overrides: key by folder name (e.g., '4_synth_struct')
// Example: '4_synth_struct' -> 'Estrutura básica de um Sintetizador'
const sectionNameOverrides: Record<string, string> = {
  '1_intro': 'Introdução',
  '2_synth_hist': 'Breve História dos Sintetizadores',
  '3_som': 'Som: Fundamentos',
  '4_synth_struct': 'Estrutura básica de um Sintetizador',
  '5_mozzi': 'Mozzi',
}

function titleCase(s: string) {
  return s
    .split(' ')
    .filter(Boolean)
    .map((w) => w.charAt(0).toUpperCase() + w.slice(1))
    .join(' ')
}

function extractInfo(path: string) {
  // Example: ./1_intro/SlideIntro.vue
  const parts = path.split('/')
  const folder = parts[1] || ''
  const file = (parts[parts.length - 1] ?? '').replace('.vue', '')

  // Section title: strip numeric prefix and prettify
  const section = folder.replace(/^\d+_/, '').replace(/[_-]/g, ' ')
  const sectionTitle = titleCase(section)

  // Slide title: remove leading "Slide" and split camel case
  const fileCore = file.replace(/^\d+_/, '') // strip numeric prefix like 01_
  const slideTitle = titleCase(
    fileCore
      .replace(/^Slide/i, '')
      .replace(/[_-]/g, ' ')
      .replace(/([A-Z])/g, ' $1')
      .replace(/(\d+)/g, ' $1')
      .replace(/\s+/g, ' ')
      .trim(),
  )

  return { folder, sectionTitle, slideTitle }
}

export interface SlideDef {
  title: string
  component: Component
}

export interface SectionDef {
  title: string
  slides: SlideDef[]
}

const slidesData = Object.entries(modules)
  .map(([path, mod]) => {
    const info = extractInfo(path)
    const m = mod as { default: Component; slideTitle?: unknown; title?: unknown }
    const overrideSlideTitle =
      (typeof m.slideTitle === 'string' && m.slideTitle) ||
      (typeof m.title === 'string' && m.title) ||
      undefined
    return {
      path,
      folder: info.folder,
      sectionTitle: sectionNameOverrides[info.folder] ?? info.sectionTitle,
      title: (overrideSlideTitle ?? info.slideTitle) as string,
      component: (m as { default: Component }).default,
    }
  })
  // Sort with natural order so 1_*, 2_* come before 10_* correctly
  .sort((a, b) => a.path.localeCompare(b.path, undefined, { numeric: true }))

// Group by section (folder)
const sections: SectionDef[] = []
for (const slide of slidesData) {
  let section = sections.find((s) => s.title === slide.sectionTitle)
  if (!section) {
    section = { title: slide.sectionTitle, slides: [] }
    sections.push(section)
  }
  section.slides.push({ title: slide.title, component: slide.component })
}

// Flatten for linear navigation
export const orderedSlides: SlideDef[] = sections.flatMap((s) => s.slides)

export { sections }
export default orderedSlides
