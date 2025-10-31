<script setup lang="ts">
import { computed, onMounted, onBeforeUnmount, ref, type Component } from 'vue'
import { useRoute, useRouter } from 'vue-router'
import slides, { sections } from '@/slides/registry'
import { ChevronLeft, ChevronRight, List } from 'lucide-vue-next'

const route = useRoute()
const router = useRouter()

const total = slides.length

const idx = computed(() => {
  const raw = (route.params.idx as string) ?? '1'
  const n = parseInt(raw, 10)
  if (Number.isNaN(n)) return 1
  if (n < 1) return 1
  if (n > total) return total
  return n
})

const currentIndex0 = computed(() => idx.value - 1)
const isFirst = computed(() => idx.value <= 1)
const isLast = computed(() => idx.value >= total)

function goTo(n: number) {
  if (n < 1 || n > total) return
  router.push({ name: 'slide', params: { idx: String(n) } })
}
function next() {
  if (!isLast.value) goTo(idx.value + 1)
}
function prev() {
  if (!isFirst.value) goTo(idx.value - 1)
}

onMounted(() => {
  const onKey = (e: KeyboardEvent) => {
    // Allow quick navigation with keyboard
    if (e.key === 'ArrowRight' || e.key === 'PageDown' || e.key === ' ') {
      e.preventDefault()
      next()
    } else if (e.key === 'ArrowLeft' || e.key === 'PageUp') {
      e.preventDefault()
      prev()
    } else if (e.key === 'm' || e.key === 'M') {
      e.preventDefault()
      toggleIndex()
    } else if (e.key === 'Escape') {
      e.preventDefault()
      closeIndex()
    }
  }
  window.addEventListener('keydown', onKey)
  onBeforeUnmount(() => window.removeEventListener('keydown', onKey))
})

const Current = computed(() => slides[currentIndex0.value]!.component)
const title = computed(() => slides[currentIndex0.value]!.title)

// Controle de estado do sumário
const showIndex = ref(false)
function closeIndex() {
  showIndex.value = false
}
function toggleIndex() {
  showIndex.value = !showIndex.value
}
function jumpTo(i: number) {
  closeIndex()
  goTo(i)
}

function getSlideIndex(slide: { component: Component }) {
  return slides.findIndex((s) => s.component === slide.component)
}

// Seções colapsáveis no sumário
const expandedSections = ref<boolean[]>(sections.map(() => true))
function toggleSection(sidx: number) {
  expandedSections.value[sidx] = !expandedSections.value[sidx]
}
</script>

<template>
  <div
    class="w-screen h-screen flex flex-col bg-background text-foreground overflow-hidden py-8"
    style="
      padding-top: calc(env(safe-area-inset-top) + 2rem);
      padding-bottom: calc(env(safe-area-inset-bottom) + 2rem);
    "
  >
    <!-- Header / progress -->
    <header class="relative px-4 text-center text-slate-500 text-sm select-none">
      <span class="ml-2 text-slate-400">({{ idx }}/{{ total }})</span>
      <br />
      <span>{{ title }}</span>
    </header>

    <!-- Slide content area, centered -->
    <main class="flex-1 flex items-center justify-center overflow-hidden min-h-0 min-w-0">
      <div
        class="w-full h-full max-w-5xl mx-auto flex items-center justify-center p-2 md:p-4 min-h-0 min-w-0"
      >
        <component :is="Current" />
      </div>
    </main>

    <!-- Navigation + dots -->
    <footer class="px-4 flex flex-col items-center justify-center gap-3">
      <!-- Dots -->
      <div class="flex items-center justify-center gap-2">
        <button
          v-for="n in total"
          :key="n"
          type="button"
          @click="goTo(n)"
          :aria-label="`Ir para o slide ${n}`"
          class="w-2.5 h-2.5 rounded-full transition-colors"
          :class="n === idx ? 'bg-blue-500' : 'bg-slate-600 hover:bg-slate-500'"
        />
      </div>

      <!-- Prev/Next buttons -->
      <div class="flex items-center justify-center gap-4">
        <button
          type="button"
          @click="prev"
          :disabled="isFirst"
          class="p-2 rounded-full bg-slate-800 text-white hover:bg-slate-700 disabled:opacity-40 disabled:cursor-not-allowed"
          title="Anterior"
          aria-label="Anterior"
        >
          <ChevronLeft class="w-5 h-5" />
        </button>
        <button
          type="button"
          @click="toggleIndex"
          class="p-2 rounded-full bg-slate-800 text-white hover:bg-slate-700"
          title="Sumário"
          aria-label="Sumário"
        >
          <List class="w-5 h-5" />
        </button>
        <button
          type="button"
          @click="next"
          :disabled="isLast"
          class="p-2 rounded-full bg-blue-600 text-white hover:bg-blue-500 disabled:opacity-40 disabled:cursor-not-allowed"
          title="Próximo"
          aria-label="Próximo"
        >
          <ChevronRight class="w-5 h-5" />
        </button>
      </div>
    </footer>

    <!-- Overlay Index -->
    <div
      v-if="showIndex"
      class="fixed inset-0 bg-black/60 backdrop-blur-sm flex items-center justify-center z-50"
      @click="closeIndex"
    >
      <div
        class="bg-slate-900 text-slate-100 rounded-lg shadow-xl w-[min(90vw,40rem)] max-h-[80vh] overflow-y-auto p-4"
        @click.stop
      >
        <div class="flex items-center justify-between mb-3 text-center">
          <h2 class="text-lg font-semibold text-center">Sumário</h2>
          <button
            type="button"
            @click="closeIndex"
            class="text-slate-300 hover:text-white"
            aria-label="Fechar"
          >
            ✕
          </button>
        </div>
        <div>
          <div v-for="(section, sidx) in sections" :key="sidx" class="mb-3">
            <button
              type="button"
              class="w-full text-left font-semibold text-slate-300 mb-1 hover:text-white flex items-center"
              @click.stop="toggleSection(sidx)"
              :aria-expanded="expandedSections[sidx] ? 'true' : 'false'"
              :aria-controls="`section-${sidx}`"
            >
              <span class="mr-2 select-none">{{ expandedSections[sidx] ? '▾' : '▸' }}</span>
              <span>{{ sidx + 1 }}. {{ section.title }}</span>
            </button>
            <ul class="ml-6 space-y-1" :id="`section-${sidx}`" v-show="expandedSections[sidx]">
              <li v-for="(s, i) in section.slides" :key="i">
                <button
                  type="button"
                  class="w-full text-left px-3 py-2 rounded hover:bg-slate-800"
                  :class="getSlideIndex(s) + 1 === idx ? 'bg-slate-800' : ''"
                  @click="jumpTo(getSlideIndex(s) + 1)"
                >
                  <span class="text-slate-400 mr-2">{{ sidx + 1 + '.' + (i + 1) }}</span
                  >{{ s.title }}
                </button>
              </li>
            </ul>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped></style>
