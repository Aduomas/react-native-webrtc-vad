import type { TurboModule } from 'react-native';
export interface Spec extends TurboModule {
    processPcm(pcmDataBase64: string, sampleRate: number): Promise<{
        success: boolean;
        isVoice?: boolean;
        processingTimeMs?: number;
        error?: string;
    }>;
    processMultiplePcm(pcmDataBase64: string, sampleRate: number, chunkSize: number): Promise<{
        success: boolean;
        results?: boolean[];
        processingTimeMs?: number;
        error?: string;
    }>;
}
declare const _default: Spec;
export default _default;
//# sourceMappingURL=NativeWebrtcVadTurboModule.d.ts.map