<script lang="ts">
// Custom slide title used by the menu and header
export const slideTitle = 'Equipe CAIXA ALTA'
</script>

<template>
  <div class="w-full h-full flex flex-col items-center justify-center text-center overflow-hidden">
    <h3 class="font-semibold text-[clamp(.9rem,2.2vmin,1.4rem)] mb-1">Equipe CAIXA ALTA</h3>

    <!-- 2x2 responsive grid that fills available space -->
    <div
      class="grid grid-cols-2 grid-rows-[1fr_1fr] gap-3 w-full h-full max-w-5xl p-2 md:p-3 place-items-stretch min-h-0 min-w-0"
    >
      <!-- Card -->
      <!-- Left column: text on left, image on right -->
      <div
        class="flex items-center rounded-lg border border-slate-700/50 p-2 md:p-3 gap-2 min-h-0 min-w-0 h-full w-full overflow-hidden"
      >
        <div class="basis-1/2 min-w-0 min-h-0 flex flex-col items-center justify-center gap-1 px-1">
          <h4 class="font-semibold text-[clamp(.85rem,1.8vmin,1.1rem)] leading-tight">Knid</h4>
          <p class="text-slate-400 text-[clamp(.75rem,1.5vmin,.95rem)] max-w-[36ch]">
            Lorem ipsum dolor sit amet, consectetur adipiscing elit. Lorem ipsum dolor sit amet,
            consectetur adipiscing elit. Lorem ipsum dolor sit amet, consectetur adipiscing elit.
            Lorem ipsum dolor sit amet, consectetur adipiscing elit.
          </p>
        </div>
        <div class="basis-1/2 h-full min-w-0 min-h-0 flex items-center justify-center px-1">
          <img
            src="@/assets/equipefotos/knid.png"
            alt="Knid"
            class="h-full w-full object-contain"
          />
        </div>
      </div>

      <!-- Right column: image on left, text on right -->
      <div
        class="flex items-center rounded-lg border border-slate-700/50 p-2 md:p-3 gap-2 min-h-0 min-w-0 h-full w-full overflow-hidden"
      >
        <div class="basis-1/2 h-full min-w-0 min-h-0 flex items-center justify-center px-1">
          <img
            src="@/assets/equipefotos/nath.png"
            alt="Nath"
            class="h-full w-full object-contain"
          />
        </div>
        <div class="basis-1/2 min-w-0 min-h-0 flex flex-col items-center justify-center gap-1 px-1">
          <h4 class="font-semibold text-[clamp(.85rem,1.8vmin,1.1rem)] leading-tight">Nath</h4>
          <p class="text-slate-400 text-[clamp(.75rem,1.5vmin,.95rem)] max-w-[36ch]">
            Lorem ipsum dolor sit amet, consectetur adipiscing elit. Lorem ipsum dolor sit amet,
            consectetur adipiscing elit. Lorem ipsum dolor sit amet, consectetur adipiscing elit.
            Lorem ipsum dolor sit amet, consectetur adipiscing elit.
          </p>
        </div>
      </div>

      <!-- Left column: text on left, image on right -->
      <div
        class="flex items-center rounded-lg border border-slate-700/50 p-2 md:p-3 gap-2 min-h-0 min-w-0 h-full w-full overflow-hidden"
      >
        <div class="basis-1/2 min-w-0 min-h-0 flex flex-col items-center justify-center gap-1 px-1">
          <h4 class="font-semibold text-[clamp(.85rem,1.8vmin,1.1rem)] leading-tight">Lucas</h4>
          <p class="text-slate-400 text-[clamp(.75rem,1.5vmin,.95rem)] max-w-[36ch]">
            Lorem ipsum dolor sit amet, consectetur adipiscing elit. Lorem ipsum dolor sit amet,
            consectetur adipiscing elit. Lorem ipsum dolor sit amet, consectetur adipiscing elit.
            Lorem ipsum dolor sit amet, consectetur adipiscing elit.
          </p>
        </div>
        <div class="basis-1/2 h-full min-w-0 min-h-0 flex items-center justify-center px-1">
          <img
            src="@/assets/equipefotos/lucas.png"
            alt="Lucas"
            class="h-full w-full object-contain"
          />
        </div>
      </div>

      <!-- Right column: image on left, text on right -->
      <div
        class="flex items-center rounded-lg border border-slate-700/50 p-2 md:p-3 gap-2 min-h-0 min-w-0 h-full w-full overflow-hidden"
      >
        <div class="basis-1/2 h-full min-w-0 min-h-0 flex items-center justify-center px-1">
          <img
            src="@/assets/equipefotos/tales.png"
            alt="Tales"
            class="h-full w-full object-contain"
          />
        </div>
        <div class="basis-1/2 min-w-0 min-h-0 flex flex-col items-center justify-center gap-1 px-1">
          <h4 class="font-semibold text-[clamp(.85rem,1.8vmin,1.1rem)] leading-tight">Tales</h4>
          <p class="text-slate-400 text-[clamp(.75rem,1.5vmin,.95rem)] max-w-[36ch]">
            Lorem ipsum dolor sit amet, consectetur adipiscing elit. Lorem ipsum dolor sit amet,
            consectetur adipiscing elit. Lorem ipsum dolor sit amet, consectetur adipiscing elit.
            Lorem ipsum dolor sit amet, consectetur adipiscing elit.
          </p>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped></style>
