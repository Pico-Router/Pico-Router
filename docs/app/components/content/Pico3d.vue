<script setup lang="ts">
import { shallowRef, onMounted } from 'vue'
import { TresCanvas } from '@tresjs/core'
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader.js'

const model = shallowRef()

onMounted(() => {
  const loader = new GLTFLoader()

  loader.load('/models/3d-pico.glb', (gltf) => {
    model.value = gltf.scene
  })
})
</script>

<template>
  <ClientOnly>
    <TresCanvas window-size>
      <TresPerspectiveCamera :position="[3, 3, 3]" />

      <TresAmbientLight :intensity="2" />

      <TresDirectionalLight
        :position="[5, 5, 5]"
        :intensity="3"
      />

      <primitive
        v-if="model"
        :object="model"
      />
    </TresCanvas>
  </ClientOnly>
</template>
