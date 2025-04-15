export declare const createVad: (mode: number) => Promise<{
    success: boolean;
    vadId?: number;
    error?: string;
}>;
export declare const processVadPcm: (pcmDataBase64: string, sampleRate: number) => Promise<{
    success: boolean;
    isVoice?: boolean;
    processingTimeMs?: number;
    error?: string;
}>;
export declare const processVadOpus: (opusDataBase64: string, sampleRate: number) => Promise<{
    success: boolean;
    isVoice?: boolean;
    processingTimeMs?: number;
    error?: string;
}>;
export declare const processMultipleVadPcm: (pcmDataBase64: string, sampleRate: number, chunkSize: number) => Promise<{
    success: boolean;
    results?: boolean[];
    processingTimeMs?: number;
    error?: string;
}>;
export declare const processMultipleVadOpus: (opusDataBase64: string, sampleRate: number, chunkSize: number) => Promise<{
    success: boolean;
    results?: boolean[];
    processingTimeMs?: number;
    error?: string;
}>;
export declare const destroyVad: () => Promise<{
    success: boolean;
    error?: string;
}>;
//# sourceMappingURL=index.d.ts.map