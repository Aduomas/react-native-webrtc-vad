import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  // Create VAD (simply initializes the singleton with mode 3)
  createVad(
    mode: number
  ): Promise<{
    success: boolean;
    vadId?: number; // Technically still here in C++, but always 1
    error?: string;
  }>;

  // Process PCM data to detect voice activity
  processVadPcm(
    pcmDataBase64: string,
    sampleRate: number
  ): Promise<{
    success: boolean;
    isVoice?: boolean;
    processingTimeMs?: number;
    error?: string;
  }>;

  // Process multiple chunks of PCM data at once
  processMultipleVadPcm(
    pcmDataBase64: string,
    sampleRate: number,
    chunkSize: number
  ): Promise<{
    success: boolean;
    results?: boolean[];
    processingTimeMs?: number;
    error?: string;
  }>;

  // Destroy VAD (does nothing, only for compatibility)
  destroyVad(
  ): Promise<{
    success: boolean;
    error?: string;
  }>;
  
  // Not implemented - returns error
  processVadOpus(
    opusDataBase64: string,
    sampleRate: number
  ): Promise<{
    success: boolean;
    isVoice?: boolean;
    processingTimeMs?: number;
    error?: string;
  }>;

  // Not implemented - returns error
  processMultipleVadOpus(
    opusDataBase64: string,
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