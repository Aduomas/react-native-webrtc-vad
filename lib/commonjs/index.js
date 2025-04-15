"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.processVadPcm = exports.processVadOpus = exports.processMultipleVadPcm = exports.processMultipleVadOpus = exports.destroyVad = exports.createVad = void 0;
var _NativeWebrtcVad = _interopRequireDefault(require("./NativeWebrtcVad"));
function _interopRequireDefault(e) { return e && e.__esModule ? e : { default: e }; }
const createVad = exports.createVad = _NativeWebrtcVad.default.createVad;
const processVadPcm = exports.processVadPcm = _NativeWebrtcVad.default.processVadPcm;
const processVadOpus = exports.processVadOpus = _NativeWebrtcVad.default.processVadOpus;
const processMultipleVadPcm = exports.processMultipleVadPcm = _NativeWebrtcVad.default.processMultipleVadPcm;
const processMultipleVadOpus = exports.processMultipleVadOpus = _NativeWebrtcVad.default.processMultipleVadOpus;
const destroyVad = exports.destroyVad = _NativeWebrtcVad.default.destroyVad;
//# sourceMappingURL=index.js.map