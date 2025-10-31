import { createRouter, createWebHistory } from 'vue-router'
import SlideView from '@/views/SlideView.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    { path: '/:idx(\\d+)?', name: 'slide', component: SlideView },
    { path: '/:pathMatch(.*)*', redirect: '/1' },
  ],
})

export default router
