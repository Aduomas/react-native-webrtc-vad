export declare function processPcm(pcmDataBase64: string, sampleRate: number): Promise<{
    success: boolean;
    isVoice?: boolean;
    processingTimeMs?: number;
    error?: string;
}>;
export declare function processMultiplePcm(pcmDataBase64: string, sampleRate: number, chunkSize: number): Promise<{
    success: boolean;
    results?: boolean[];
    processingTimeMs?: number;
    error?: string;
}>;
//# sourceMappingURL=index.d.ts.map