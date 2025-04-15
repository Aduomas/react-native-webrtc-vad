"use strict";

import WebrtcVad from './NativeWebrtcVadTurboModule';
export function processPcm(pcmDataBase64, sampleRate) {
  return WebrtcVad.processPcm(pcmDataBase64, sampleRate);
}
export function processMultiplePcm(pcmDataBase64, sampleRate, chunkSize) {
  return WebrtcVad.processMultiplePcm(pcmDataBase64, sampleRate, chunkSize);
}
//# sourceMappingURL=index.js.map