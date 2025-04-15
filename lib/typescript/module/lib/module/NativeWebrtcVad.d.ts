import type { TurboModule } from 'react-native';
export interface Spec extends TurboModule {
    createVad(mode: number): Promise<{
        success: boolean;
        vadId?: number;
        error?: string;
    }>;
    processVadPcm(pcmDataBase64: string, sampleRate: number): Promise<{
        success: boolean;
        isVoice?: boolean;
        processingTimeMs?: number;
        error?: string;
    }>;
    processMultipleVadPcm(pcmDataBase64: string, sampleRate: number, chunkSize: number): Promise<{
        success: boolean;
        results?: boolean[];
        processingTimeMs?: number;
        error?: string;
    }>;
    destroyVad(): Promise<{
        success: boolean;
        error?: string;
    }>;
    processVadOpus(opusDataBase64: string, sampleRate: number): Promise<{
        success: boolean;
        isVoice?: boolean;
        processingTimeMs?: number;
        error?: string;
    }>;
    processMultipleVadOpus(opusDataBase64: string, sampleRate: number, chunkSize: number): Promise<{
        success: boolean;
        results?: boolean[];
        processingTimeMs?: number;
        error?: string;
    }>;
}
declare const _default: Spec;
export default _default;
//# sourceMappingURL=NativeWebrtcVad.d.ts.map