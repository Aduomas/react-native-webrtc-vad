import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  // Process PCM data to detect voice activity
  processPcm(
    pcmDataBase64: string,
    sampleRate: number
  ): Promise<{
    success: boolean;
    isVoice?: boolean;
    processingTimeMs?: number;
    error?: string;
  }>;

  // Process multiple chunks of PCM data at once
  processMultiplePcm(
    pcmDataBase64: string,
    sampleRate: number,
    chunkSize: number
  ): Promise<{
    success: boolean;
    results?: boolean[];
    processingTimeMs?: number;
    error?: string;
  }>;
}

export default TurboModuleRegistry.getEnforcing<Spec>('WebrtcVad'); 