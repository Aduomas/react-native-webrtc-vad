import WebrtcVad from './NativeWebrtcVadTurboModule';

export function processPcm(pcmDataBase64: string, sampleRate: number) {
  return WebrtcVad.processPcm(pcmDataBase64, sampleRate);
}

export function processMultiplePcm(
  pcmDataBase64: string, 
  sampleRate: number, 
  chunkSize: number
) {
  return WebrtcVad.processMultiplePcm(pcmDataBase64, sampleRate, chunkSize);
}
