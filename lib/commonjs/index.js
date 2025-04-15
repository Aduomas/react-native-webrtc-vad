"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.processMultiplePcm = processMultiplePcm;
exports.processPcm = processPcm;
var _NativeWebrtcVadTurboModule = _interopRequireDefault(require("./NativeWebrtcVadTurboModule"));
function _interopRequireDefault(e) { return e && e.__esModule ? e : { default: e }; }
function processPcm(pcmDataBase64, sampleRate) {
  return _NativeWebrtcVadTurboModule.default.processPcm(pcmDataBase64, sampleRate);
}
function processMultiplePcm(pcmDataBase64, sampleRate, chunkSize) {
  return _NativeWebrtcVadTurboModule.default.processMultiplePcm(pcmDataBase64, sampleRate, chunkSize);
}
//# sourceMappingURL=index.js.map