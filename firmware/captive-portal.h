#pragma once

#include <Arduino.h>

// ======================================================================
// --- WEB INTERFACE HTML ---
// ======================================================================

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Sesame Drone Controller</title>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
  <meta charset="UTF-8">
  <style>
    :root {
      --content-color: #00e5ff;
      --content-color-dark: #00b4cc;
      --content-color-darker: #008899;
      --bg-base: #0a0a0a;
      --bg-surface: #141414;
      --bg-surface-alt: #1a1a1a;
      --border-color: #333333;
      --border-focus: #555555;
      --text-main: #ffffff;
      --text-muted: #888888;
    }
    
    * {
      user-select: none;
      -webkit-user-select: none;
      -webkit-touch-callout: none;
      box-sizing: border-box;
    }
    
    body { 
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Helvetica, Arial, sans-serif; 
      text-align: center; 
      background: var(--bg-base);
      color: var(--text-main); 
      touch-action: manipulation; 
      margin: 0;
      padding: 12px;
      overflow-x: hidden;
      min-height: 100vh;
    }
    
    h2 { 
      margin: 8px 0 4px 0;
      color: var(--text-main);
      font-size: 24px;
      font-weight: 700;
      letter-spacing: 1.5px;
      text-transform: uppercase;
    }
    
    .subtitle {
      font-size: 11px;
      color: var(--content-color);
      letter-spacing: 2px;
      text-transform: uppercase;
      margin-bottom: 12px;
      font-weight: 600;
    }
    
    /* Command Queue Status */
    .command-queue {
      font-size: 11px;
      color: var(--text-muted);
      margin-bottom: 14px;
      letter-spacing: 1px;
      text-transform: uppercase;
    }
    .command-queue.full {
      color: #ff3333;
      font-weight: 700;
    }
    
    /* Section Containers */
    .sections-container {
      display: flex;
      flex-direction: column;
      gap: 14px;
      max-width: 1200px;
      margin: 0 auto;
    }
    
    .section {
      background: var(--bg-surface);
      border: 1px solid var(--border-color);
      border-radius: 8px;
      padding: 16px;
      margin: 0 auto;
      width: 100%;
      max-width: 440px;
    }
    
    .section-title {
      font-size: 12px;
      font-weight: 700;
      color: var(--content-color);
      margin: 0 0 14px 0;
      text-transform: uppercase;
      letter-spacing: 1.5px;
      text-align: left;
    }
    
    /* Button Base Styles */
    button { 
      background: var(--bg-surface-alt);
      border: 1px solid var(--border-color); 
      color: var(--text-main); 
      padding: 14px; 
      font-size: 15px; 
      border-radius: 6px; 
      cursor: pointer; 
      font-weight: 600;
      letter-spacing: 0.5px;
      transition: background 0.05s, border-color 0.05s;
    }
    button:active { 
      background: #2a2a2a; 
      border-color: var(--border-focus);
    }
    
    /* Dedicated Drone Mode Lock Button (Between Movement and Poses) */
    .drone-mode-wrap {
      width: 100%;
      max-width: 440px;
      margin: 0 auto;
    }
    .btn-drone-master {
      background: #002b36;
      border: 2px solid var(--content-color);
      color: var(--content-color);
      width: 100%;
      padding: 16px;
      font-size: 16px;
      font-weight: 800;
      letter-spacing: 2px;
      text-transform: uppercase;
      border-radius: 8px;
      display: block;
    }
    .btn-drone-master:active {
      background: #004455;
      color: #ffffff;
      border-color: #ffffff;
    }
    
    /* D-Pad Controls */
    .dpad-container { 
      display: flex; 
      flex-direction: column;
      align-items: center;
      gap: 12px;
      width: 100%;
    }
    .dpad { 
      display: grid; 
      grid-template-columns: repeat(3, 1fr); 
      grid-template-rows: repeat(2, 1fr); 
      gap: 10px;
      width: 100%;
      max-width: 280px;
      aspect-ratio: 3 / 2;
    }
    .dpad button { 
      font-size: 28px; 
      border: 1px solid var(--border-color); 
      background: var(--bg-surface-alt);
      color: #ffffff;
      width: 100%;
      height: 100%;
      min-height: 64px;
      display: flex;
      align-items: center;
      justify-content: center;
      border-radius: 6px;
    }
    .dpad button:active {
      background: #333333;
      border-color: #666666;
    }
    .spacer { 
      visibility: hidden; 
    }
    
    /* Pose Grid */
    .grid { 
      display: grid; 
      grid-template-columns: repeat(3, 1fr); 
      gap: 8px; 
    }
    .btn-pose { 
      background: var(--bg-surface-alt);
      border: 1px solid var(--border-color);
      padding: 13px 6px;
      font-size: 14px;
      font-weight: 600;
      color: #eeeeee;
      border-radius: 6px;
      text-transform: uppercase;
      letter-spacing: 0.5px;
    }
    .btn-pose:active { 
      background: #2a2a2a;
      border-color: var(--border-focus);
    }
    .btn-pose.btn-drone {
      border: 1px solid var(--content-color);
      color: var(--content-color);
      font-weight: 700;
    }
    
    /* Stop Button */
    .btn-stop-all { 
      background: #8b0000;
      border: 1px solid #ff4444;
      width: 100%; 
      font-size: 16px; 
      padding: 15px; 
      color: #ffffff;
      text-transform: uppercase;
      letter-spacing: 2px;
      font-weight: 800;
      border-radius: 6px;
    }
    .btn-stop-all:active { 
      background: #b30000;
      border-color: #ffffff;
    }
    
    .btn-settings { 
      background: var(--bg-surface-alt);
      border: 1px solid var(--border-color);
      padding: 12px 20px;
      font-size: 14px;
      color: var(--text-main);
      border-radius: 6px;
      font-weight: 600;
    }
    
    /* Motor Controls */
    .lock-indicator {
      font-size: 11px;
      color: #ff4444;
      text-align: center;
      margin-top: 5px;
      display: none;
      font-weight: 600;
      text-transform: uppercase;
      letter-spacing: 1px;
    }
    .lock-indicator.active {
      display: block;
    }
    
    .motor-controls {
      margin-top: 10px;
    }
    .motor-slider {
      margin: 14px 0;
    }
    .motor-slider label {
      display: flex;
      justify-content: space-between;
      font-size: 12px;
      font-weight: 600;
      color: var(--text-muted);
      margin-bottom: 4px;
    }
    .motor-slider input[type="range"] {
      width: 100%;
      height: 6px;
      background: #222222;
      border-radius: 3px;
      outline: none;
      -webkit-appearance: none;
    }
    .motor-slider input[type="range"]::-webkit-slider-thumb {
      -webkit-appearance: none;
      width: 18px;
      height: 18px;
      background: var(--content-color);
      border-radius: 50%;
      cursor: pointer;
      border: none;
    }
    .motor-slider input[type="range"]::-moz-range-thumb {
      width: 18px;
      height: 18px;
      background: var(--content-color);
      border-radius: 50%;
      cursor: pointer;
      border: none;
    }
    .motor-slider input[type="range"]:disabled {
      opacity: 0.35;
      cursor: not-allowed;
    }
    
    /* Gamepad Status */
    .gamepad-status {
      font-size: 12px;
      padding: 6px 12px;
      border-radius: 4px;
      border: 1px solid var(--border-color);
      color: var(--text-muted);
      background: var(--bg-surface-alt);
      display: inline-block;
      font-weight: 600;
      letter-spacing: 0.5px;
    }
    .gamepad-status.connected {
      border-color: #00e676;
      color: #00e676;
    }
    
    /* Settings Panel */
    .settings-panel { 
      display: none; 
      position: fixed; 
      top: 0; 
      left: 0; 
      width: 100%; 
      height: 100%; 
      background: rgba(0,0,0,0.92); 
      z-index: 200; 
      overflow-y: auto;
    }
    .settings-content { 
      background: var(--bg-surface);
      border: 1px solid var(--border-focus); 
      max-width: 420px; 
      margin: 25px auto; 
      padding: 22px; 
      border-radius: 8px; 
      text-align: left; 
    }
    .settings-content h3 { 
      color: var(--text-main); 
      margin-top: 0; 
      text-align: center;
      font-size: 20px;
      letter-spacing: 1px;
      text-transform: uppercase;
    }
    .settings-section {
      margin: 16px 0;
      padding: 14px;
      background: var(--bg-surface-alt);
      border: 1px solid var(--border-color);
      border-radius: 6px;
    }
    .settings-section h4 {
      color: var(--content-color);
      margin: 0 0 10px 0;
      font-size: 12px;
      text-transform: uppercase;
      letter-spacing: 1px;
    }
    .settings-content label { 
      display: block; 
      margin-top: 10px; 
      font-weight: 600; 
      color: #cccccc;
      font-size: 12px;
    }
    .settings-content input, 
    .settings-content select { 
      width: 100%; 
      padding: 10px; 
      margin-top: 4px; 
      background: #0a0a0a; 
      color: #ffffff; 
      border: 1px solid var(--border-color); 
      border-radius: 4px; 
      font-size: 14px;
    }
    .settings-content input:focus,
    .settings-content select:focus {
      border-color: var(--content-color);
      outline: none;
    }
    .btn-save { 
      background: #006064;
      border: 1px solid var(--content-color);
      width: 100%; 
      margin-top: 20px; 
      color: #ffffff; 
      font-weight: 700;
      letter-spacing: 1px;
      text-transform: uppercase;
    }
    .btn-save:active {
      background: #00838f;
    }
    .btn-close { 
      background: #222222;
      border: 1px solid var(--border-color);
      width: 100%; 
      margin-top: 10px; 
      color: #ffffff; 
      font-weight: 600;
      letter-spacing: 1px;
      text-transform: uppercase;
    }
    .btn-close:active {
      background: #333333;
    }
    
    /* Drone Mode Lock Overlay (High Contrast, Clean & Effective, No Emojis) */
    .drone-lock-overlay {
      position: fixed;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
      background: rgba(0, 0, 0, 0.94);
      z-index: 1000;
      display: flex;
      align-items: center;
      justify-content: center;
      padding: 16px;
      touch-action: none;
    }
    .drone-lock-modal {
      background: #111111;
      border: 2px solid var(--content-color);
      border-radius: 10px;
      padding: 28px 20px;
      max-width: 380px;
      width: 100%;
      text-align: center;
    }
    .drone-lock-header {
      font-size: 13px;
      color: var(--content-color);
      font-weight: 700;
      letter-spacing: 2px;
      text-transform: uppercase;
      margin-bottom: 6px;
    }
    .drone-lock-title {
      color: #ffffff;
      font-size: 22px;
      font-weight: 800;
      letter-spacing: 2px;
      margin-bottom: 12px;
      text-transform: uppercase;
    }
    .drone-lock-badge {
      display: inline-block;
      background: #1a1a1a;
      color: #ffffff;
      border: 1px solid #444444;
      font-size: 11px;
      font-weight: 700;
      letter-spacing: 1.5px;
      padding: 4px 12px;
      border-radius: 4px;
      margin-bottom: 16px;
      text-transform: uppercase;
    }
    .drone-lock-desc {
      color: #888888;
      font-size: 13px;
      line-height: 1.5;
      margin-bottom: 24px;
    }
    .unlock-slider-wrap {
      width: 100%;
      touch-action: none;
    }
    .unlock-track {
      position: relative;
      width: 100%;
      height: 52px;
      background: #181818;
      border: 1px solid #444444;
      border-radius: 26px;
      overflow: hidden;
      touch-action: none;
    }
    .unlock-fill {
      position: absolute;
      top: 0;
      left: 0;
      height: 100%;
      width: 0;
      background: #00363a;
      pointer-events: none;
      border-radius: 26px;
    }
    .unlock-text {
      position: absolute;
      inset: 0;
      display: flex;
      align-items: center;
      justify-content: center;
      color: #cccccc;
      font-size: 12px;
      font-weight: 700;
      letter-spacing: 2px;
      text-transform: uppercase;
      pointer-events: none;
      padding-left: 28px;
    }
    .unlock-thumb {
      position: absolute;
      top: 3px;
      left: 3px;
      width: 44px;
      height: 44px;
      background: var(--content-color);
      border-radius: 50%;
      display: flex;
      align-items: center;
      justify-content: center;
      color: #000000;
      font-size: 14px;
      font-weight: 900;
      letter-spacing: -1px;
      cursor: grab;
      z-index: 2;
      touch-action: none;
      border: none;
    }
    .unlock-thumb:active {
      cursor: grabbing;
      background: #ffffff;
    }

    /* Desktop Layout */
    @media (min-width: 1024px) {
      body {
        padding: 24px;
      }
      .section {
        padding: 20px;
        max-width: 440px;
      }
      .sections-container {
        flex-direction: row;
        justify-content: center;
        align-items: flex-start;
        gap: 30px;
      }
      .section-column {
        flex: 0 1 440px;
        display: flex;
        flex-direction: column;
        gap: 14px;
      }
    }
  </style>
</head>
<body>
  <h2>Sesame Drone Controller</h2>
  <div class="subtitle">Flight &amp; Ground Station</div>
  <div class="command-queue" id="queueStatus">Command Queue: 0/3</div>

  <div class="sections-container">
    <div class="section-column">
      <!-- Movement Control Section -->
      <div class="section">
        <div class="section-title">Movement Control</div>
        <div class="dpad-container">
          <div class="dpad">
            <div class="spacer"></div>
            <button onmousedown="move('forward')" onmouseup="stop()" ontouchstart="move('forward')" ontouchend="stop()">&#9650;</button>
            <div class="spacer"></div>
            
            <button onmousedown="move('left')" onmouseup="stop()" ontouchstart="move('left')" ontouchend="stop()">&#9664;</button>
            <button onmousedown="move('backward')" onmouseup="stop()" ontouchstart="move('backward')" ontouchend="stop()">&#9660;</button>
            <button onmousedown="move('right')" onmouseup="stop()" ontouchstart="move('right')" ontouchend="stop()">&#9654;</button>
          </div>
          <button class="btn-stop-all" onclick="stop()">STOP ALL</button>
        </div>
      </div>

      <!-- Drone Mode Button: Moved in between Movement and Poses -->
      <div class="drone-mode-wrap">
        <button class="btn-drone-master" onclick="enterDroneMode()">DRONE MODE &mdash; LOCK</button>
      </div>

      <!-- Poses & Animations Section (Safe for Drone clearance) -->
      <div class="section">
        <div class="section-title">Poses &amp; Animations</div>
        <div class="grid">
          <button class="btn-pose" onclick="pose('rest')">Rest</button>
          <button class="btn-pose" onclick="pose('stand')">Stand</button>
          <button class="btn-pose btn-drone" onclick="enterDroneMode()">Drone</button>
          <button class="btn-pose" onclick="pose('dead')">Dead</button>
          <button class="btn-pose" onclick="pose('pushup')">Pushup</button>
          <button class="btn-pose" onclick="pose('bow')">Bow</button>
          <button class="btn-pose" onclick="pose('swim')">Swim</button>
          <button class="btn-pose" onclick="pose('shake')">Shake</button>
          <button class="btn-pose" onclick="pose('crab')">Crab</button>
        </div>
      </div>
    </div>

    <div class="section-column">
      <!-- Settings & Status Section -->
      <div class="section">
        <div class="section-title">System</div>
        <button class="btn-settings" onclick="openSettings()">Settings</button>
        <div style="margin-top: 15px;">
          <div id="gamepadStatus" class="gamepad-status">Gamepad disconnected</div>
        </div>
      </div>
    </div>
  </div>

  <!-- Settings Modal Panel -->
  <div id="settingsPanel" class="settings-panel">
    <div class="settings-content">
      <h3>Settings</h3>
      
      <div class="settings-section">
        <h4>Animation Parameters</h4>
        <label>Frame Delay (ms):</label>
        <input type="number" id="frameDelay" min="1" max="1000" step="1">
        <label>Walk Cycles:</label>
        <input type="number" id="walkCycles" min="1" max="50" step="1">
      </div>

      <div class="settings-section">
        <h4>Motor Settings</h4>
        <label>Motor Current Delay (ms):</label>
        <input type="number" id="motorCurrentDelay" min="0" max="500" step="1">
        <label>Motor Speed:</label>
        <select id="motorSpeed">
          <option value="slow">Slow</option>
          <option value="medium" selected>Medium</option>
          <option value="fast">Fast</option>
        </select>
      </div>

      <div class="settings-section">
        <h4>Theme</h4>
        <label>Accent Color:</label>
        <select id="themeColor">
          <option value="#00e5ff">Electric Cyan (Default)</option>
          <option value="#ffffff">Clean White</option>
          <option value="#00e676">Matrix Green</option>
          <option value="#ffb300">Warning Amber</option>
          <option value="#ff3d00">Signal Red</option>
          <option value="#d500f9">Neon Purple</option>
          <option value="custom">Custom</option>
        </select>
        <input type="color" id="customColor" value="#00e5ff" style="margin-top: 10px; display: none;">
      </div>

      <div class="settings-section">
        <h4>WiFi / Network</h4>
        <div id="wifiStatus" style="font-size:12px; color:#cccccc; margin-bottom:10px;">Checking&hellip;</div>
        <label>Network:</label>
        <select id="wifiSsid">
          <option value="">&mdash; scan for networks &mdash;</option>
        </select>
        <label style="margin-top:10px;">
          <input type="checkbox" id="wifiManual" style="width:auto; margin-right:8px;" onchange="toggleManualSsid()">
          Enter name manually (hidden network)
        </label>
        <input type="text" id="wifiSsidManual" placeholder="Network name" style="display:none;">
        <label>Password:</label>
        <input type="password" id="wifiPass" placeholder="WiFi password">
        <button class="btn-settings" style="width:100%; margin-top:12px;" onclick="scanWifi()">Scan for Networks</button>
        <button class="btn-settings" style="width:100%; margin-top:8px;" onclick="connectWifi()">Connect</button>
        <div id="wifiResult" style="font-size:12px; margin-top:10px; min-height:18px;"></div>
      </div>

      <button class="btn-settings" style="width: 100%; margin-top: 16px;" onclick="openMotorControl()">Manual Motor Control</button>

      <button class="btn-save" onclick="saveSettings()">Save Settings</button>
      <button class="btn-close" onclick="closeSettings()">Close</button>
    </div>
  </div>

  <!-- Manual Motor Control Panel -->
  <div id="motorControlPanel" class="settings-panel">
    <div class="settings-content">
      <h3>Manual Motor Control</h3>
      <div class="lock-indicator" id="lockIndicator">Locked during animations</div>
      
      <div class="settings-section">
        <div class="motor-controls">
          <div class="motor-slider">
            <label><span>S0 R1</span><span id="m1val">90&deg;</span></label>
            <input type="range" id="motor1" min="0" max="180" value="90" oninput="updateMotor(1, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S1 R2</span><span id="m2val">90&deg;</span></label>
            <input type="range" id="motor2" min="0" max="180" value="90" oninput="updateMotor(2, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S2 L1</span><span id="m3val">90&deg;</span></label>
            <input type="range" id="motor3" min="0" max="180" value="90" oninput="updateMotor(3, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S3 L2</span><span id="m4val">90&deg;</span></label>
            <input type="range" id="motor4" min="0" max="180" value="90" oninput="updateMotor(4, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S4 R4</span><span id="m5val">90&deg;</span></label>
            <input type="range" id="motor5" min="0" max="180" value="90" oninput="updateMotor(5, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S5 R3</span><span id="m6val">90&deg;</span></label>
            <input type="range" id="motor6" min="0" max="180" value="90" oninput="updateMotor(6, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S6 L3</span><span id="m7val">90&deg;</span></label>
            <input type="range" id="motor7" min="0" max="180" value="90" oninput="updateMotor(7, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S7 L4</span><span id="m8val">90&deg;</span></label>
            <input type="range" id="motor8" min="0" max="180" value="90" oninput="updateMotor(8, this.value)">
          </div>
        </div>
      </div>

      <button class="btn-close" onclick="closeMotorControl()">Close</button>
    </div>
  </div>

  <!-- Drone Mode Full-Screen Lock Overlay (High Contrast, Clean & Effective, No Emojis) -->
  <div id="droneLockOverlay" class="drone-lock-overlay" style="display: none;">
    <div class="drone-lock-modal">
      <div class="drone-lock-header">Flight Interlock</div>
      <div class="drone-lock-title">Drone Mode Active</div>
      <div class="drone-lock-badge">Controller Locked</div>
      <div class="drone-lock-desc">
        Sesame is locked into drone flight pose.<br>
        All controller inputs are disabled until unlocked.
      </div>
      
      <div class="unlock-slider-wrap">
        <div class="unlock-track" id="unlockTrack">
          <div class="unlock-fill" id="unlockFill"></div>
          <div class="unlock-text" id="unlockText">Slide to Unlock &rsaquo;&rsaquo;&rsaquo;</div>
          <div class="unlock-thumb" id="unlockThumb">
            <span id="unlockThumbIcon">&gt;&gt;</span>
          </div>
        </div>
      </div>
    </div>
  </div>

<script>
// Command queue management - max 3 commands
let commandQueue = 0;
const MAX_COMMANDS = 3;
let motorsLocked = false;
let isDroneMode = false;
let isDraggingUnlock = false;
let unlockStartX = 0;

// Load theme on page load & initialize slider
document.addEventListener('DOMContentLoaded', () => {
  loadTheme();
  initUnlockSlider();
});

function loadTheme() {
  const savedColor = localStorage.getItem('themeColor') || '#00e5ff';
  applyTheme(savedColor);
}

function applyTheme(color) {
  const root = document.documentElement;
  root.style.setProperty('--content-color', color);
  
  const rgb = hexToRgb(color);
  if (rgb) {
    const dark = `rgb(${Math.max(0, rgb.r - 25)}, ${Math.max(0, rgb.g - 25)}, ${Math.max(0, rgb.b - 25)})`;
    const darker = `rgb(${Math.max(0, rgb.r - 50)}, ${Math.max(0, rgb.g - 50)}, ${Math.max(0, rgb.b - 50)})`;
    root.style.setProperty('--content-color-dark', dark);
    root.style.setProperty('--content-color-darker', darker);
  }
}

function hexToRgb(hex) {
  const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result ? {
    r: parseInt(result[1], 16),
    g: parseInt(result[2], 16),
    b: parseInt(result[3], 16)
  } : null;
}

function updateQueueStatus() {
  const queueEl = document.getElementById('queueStatus');
  queueEl.textContent = `Command Queue: ${commandQueue}/${MAX_COMMANDS}`;
  if (commandQueue >= MAX_COMMANDS) {
    queueEl.classList.add('full');
  } else {
    queueEl.classList.remove('full');
  }
}

function canSendCommand() {
  return !isDroneMode && commandQueue < MAX_COMMANDS;
}

function incrementQueue() {
  commandQueue++;
  updateQueueStatus();
  setTimeout(() => {
    if (commandQueue > 0) {
      commandQueue--;
    }
    updateQueueStatus();
  }, 1000);
}

function lockMotors(duration = 3000) {
  motorsLocked = true;
  const lockEl = document.getElementById('lockIndicator');
  if (lockEl) lockEl.classList.add('active');
  for (let i = 1; i <= 8; i++) {
    const slider = document.getElementById('motor' + i);
    if (slider) slider.disabled = true;
  }
  setTimeout(() => {
    motorsLocked = false;
    if (lockEl) lockEl.classList.remove('active');
    for (let i = 1; i <= 8; i++) {
      const slider = document.getElementById('motor' + i);
      if (slider) slider.disabled = false;
    }
  }, duration);
}

// Drone mode lock & unlock handlers
function enterDroneMode() {
  if (isDroneMode) return;
  isDroneMode = true;
  commandQueue = 0;
  updateQueueStatus();
  
  // Command robot into drone pose
  fetch('/cmd?pose=drone').catch(console.log);
  
  // Show full lock overlay
  const overlay = document.getElementById('droneLockOverlay');
  if (overlay) overlay.style.display = 'flex';
  resetUnlockSlider();
}

function exitDroneMode() {
  isDroneMode = false;
  const overlay = document.getElementById('droneLockOverlay');
  if (overlay) overlay.style.display = 'none';
  resetUnlockSlider();
  stop();
}

function resetUnlockSlider() {
  const thumb = document.getElementById('unlockThumb');
  const fill = document.getElementById('unlockFill');
  const text = document.getElementById('unlockText');
  const icon = document.getElementById('unlockThumbIcon');
  if (thumb) {
    thumb.style.transition = 'transform 0.2s ease-out';
    thumb.style.transform = 'translateX(0px)';
  }
  if (fill) fill.style.width = '0px';
  if (text) text.style.opacity = '1';
  if (icon) icon.textContent = '>>';
  isDraggingUnlock = false;
}

function initUnlockSlider() {
  const track = document.getElementById('unlockTrack');
  const thumb = document.getElementById('unlockThumb');
  const fill = document.getElementById('unlockFill');
  const text = document.getElementById('unlockText');
  const icon = document.getElementById('unlockThumbIcon');
  if (!track || !thumb) return;

  function getClientX(e) {
    if (e.touches && e.touches.length > 0) return e.touches[0].clientX;
    if (e.changedTouches && e.changedTouches.length > 0) return e.changedTouches[0].clientX;
    return e.clientX;
  }

  function onStart(e) {
    if (!isDroneMode) return;
    isDraggingUnlock = true;
    unlockStartX = getClientX(e);
    thumb.style.transition = 'none';
    if (e.cancelable) e.preventDefault();
  }

  function onMove(e) {
    if (!isDraggingUnlock || !isDroneMode) return;
    if (e.cancelable) e.preventDefault();
    const clientX = getClientX(e);
    const maxDrag = track.clientWidth - thumb.clientWidth - 6;
    let delta = clientX - unlockStartX;
    if (delta < 0) delta = 0;
    if (delta > maxDrag) delta = maxDrag;

    thumb.style.transform = `translateX(${delta}px)`;
    if (fill) fill.style.width = `${delta + thumb.clientWidth / 2}px`;
    if (text) {
      const progress = maxDrag > 0 ? (delta / maxDrag) : 0;
      text.style.opacity = String(Math.max(0, 1 - progress * 1.5));
    }

    if (maxDrag > 0 && delta >= maxDrag * 0.88) {
      // Unlocked threshold reached!
      isDraggingUnlock = false;
      if (icon) icon.textContent = 'OK';
      if (fill) fill.style.width = '100%';
      thumb.style.transition = 'transform 0.1s ease-out';
      thumb.style.transform = `translateX(${maxDrag}px)`;
      setTimeout(() => {
        exitDroneMode();
      }, 150);
    }
  }

  function onEnd() {
    if (!isDraggingUnlock) return;
    isDraggingUnlock = false;
    resetUnlockSlider();
  }

  thumb.addEventListener('touchstart', onStart, { passive: false });
  window.addEventListener('touchmove', onMove, { passive: false });
  window.addEventListener('touchend', onEnd);
  window.addEventListener('touchcancel', onEnd);

  thumb.addEventListener('mousedown', onStart);
  window.addEventListener('mousemove', onMove);
  window.addEventListener('mouseup', onEnd);
}

function move(dir) { 
  if (!canSendCommand()) return;
  incrementQueue();
  fetch('/cmd?go=' + dir).catch(console.log); 
}

function stop() { 
  if (isDroneMode) return;
  commandQueue = 0;
  updateQueueStatus();
  fetch('/cmd?stop=1').catch(console.log); 
}

function pose(name) { 
  if (name === 'drone') {
    enterDroneMode();
    return;
  }
  if (!canSendCommand()) return;
  incrementQueue();
  lockMotors(3000);
  fetch('/cmd?pose=' + name).catch(console.log); 
}

function updateMotor(motorNum, value) {
  if (isDroneMode || motorsLocked) return;
  const valEl = document.getElementById('m' + motorNum + 'val');
  if (valEl) valEl.textContent = value + '\u00B0';
  if (!canSendCommand()) return;
  incrementQueue();
  fetch('/cmd?motor=' + motorNum + '&value=' + value).catch(console.log);
}

function openSettings() {
  if (isDroneMode) return;
  loadWifiStatus();
  fetch('/getSettings').then(r => r.json()).then(data => {
    document.getElementById('frameDelay').value = data.frameDelay || 100;
    document.getElementById('walkCycles').value = data.walkCycles || 10;
    document.getElementById('motorCurrentDelay').value = data.motorCurrentDelay || 20;
    document.getElementById('motorSpeed').value = data.motorSpeed || 'medium';
    
    // Load theme settings
    const savedColor = localStorage.getItem('themeColor') || '#00e5ff';
    const colorSelect = document.getElementById('themeColor');
    const customColorInput = document.getElementById('customColor');
    
    let matchFound = false;
    for (let option of colorSelect.options) {
      if (option.value === savedColor) {
        colorSelect.value = savedColor;
        matchFound = true;
        break;
      }
    }
    
    if (!matchFound) {
      colorSelect.value = 'custom';
      customColorInput.value = savedColor;
      customColorInput.style.display = 'block';
    }
    
    document.getElementById('settingsPanel').style.display = 'block';
  }).catch(() => {
    document.getElementById('frameDelay').value = 100;
    document.getElementById('walkCycles').value = 10;
    document.getElementById('motorCurrentDelay').value = 20;
    
    const savedColor = localStorage.getItem('themeColor') || '#00e5ff';
    document.getElementById('themeColor').value = savedColor;
    
    document.getElementById('settingsPanel').style.display = 'block';
  });
  
  document.getElementById('themeColor').addEventListener('change', function() {
    const customColorInput = document.getElementById('customColor');
    if (this.value === 'custom') {
      customColorInput.style.display = 'block';
    } else {
      customColorInput.style.display = 'none';
      applyTheme(this.value);
    }
  });
  
  document.getElementById('customColor').addEventListener('input', function() {
    applyTheme(this.value);
  });
}

function closeSettings() { 
  document.getElementById('settingsPanel').style.display = 'none'; 
}

function openMotorControl() {
  if (isDroneMode) return;
  document.getElementById('motorControlPanel').style.display = 'block';
}

function closeMotorControl() {
  document.getElementById('motorControlPanel').style.display = 'none';
}

function saveSettings() {
  const fd = document.getElementById('frameDelay').value;
  const wc = document.getElementById('walkCycles').value;
  const mcd = document.getElementById('motorCurrentDelay').value;
  const ms = document.getElementById('motorSpeed').value;
  
  const colorSelect = document.getElementById('themeColor');
  const customColorInput = document.getElementById('customColor');
  const themeColor = colorSelect.value === 'custom' ? customColorInput.value : colorSelect.value;
  localStorage.setItem('themeColor', themeColor);
  applyTheme(themeColor);
  
  fetch(`/setSettings?frameDelay=${fd}&walkCycles=${wc}&motorCurrentDelay=${mcd}&motorSpeed=${ms}`)
    .then(() => closeSettings())
    .catch(() => closeSettings());
}

function toggleManualSsid() {
  const manual = document.getElementById('wifiManual').checked;
  document.getElementById('wifiSsidManual').style.display = manual ? 'block' : 'none';
  document.getElementById('wifiSsid').style.display = manual ? 'none' : 'block';
}

function appendRobotLink(parent, host, ip) {
  const a = document.createElement('a');
  a.href = 'http://' + host;
  a.textContent = 'http://' + host;
  a.style.color = 'var(--content-color)';
  parent.appendChild(a);
  parent.appendChild(document.createTextNode(' (' + ip + ')'));
}

function appendRobotAddress(parent, d) {
  if (d.mdns) {
    appendRobotLink(parent, d.host, d.ip);
  } else {
    parent.appendChild(document.createTextNode('http://' + d.ip));
  }
}

function loadWifiStatus() {
  fetch('/api/wifi/status').then(r => r.json()).then(d => {
    const el = document.getElementById('wifiStatus');
    el.textContent = '';
    if (d.connected) {
      el.appendChild(document.createTextNode('Connected to '));
      const b = document.createElement('b');
      b.textContent = d.ssid;
      el.appendChild(b);
      el.appendChild(document.createTextNode(' — '));
      appendRobotAddress(el, d);
    } else if (d.connecting) {
      el.textContent = 'Connecting…';
    } else {
      el.textContent = 'Not connected (Access Point mode only).';
    }
  }).catch(() => {
    document.getElementById('wifiStatus').textContent = 'Status unavailable.';
  });
}

function scanWifi() {
  document.getElementById('wifiResult').textContent = 'Scanning…';
  pollWifiScan(0);
}

function pollWifiScan(attempt) {
  const sel = document.getElementById('wifiSsid');
  const result = document.getElementById('wifiResult');
  fetch('/api/wifi/scan').then(r => r.json()).then(data => {
    if (!Array.isArray(data)) {
      if (attempt < 20) setTimeout(() => pollWifiScan(attempt + 1), 1000);
      else result.textContent = 'Scan timed out.';
      return;
    }
    const best = new Map();
    data.forEach(n => {
      if (!n.ssid) return;
      if (!best.has(n.ssid) || n.rssi > best.get(n.ssid).rssi) best.set(n.ssid, n);
    });
    const nets = Array.from(best.values()).sort((a, b) => b.rssi - a.rssi);
    sel.textContent = '';
    const ph = document.createElement('option');
    ph.value = '';
    ph.textContent = '— select network —';
    sel.appendChild(ph);
    nets.forEach(n => {
      const pct = Math.min(100, Math.max(0, 2 * (n.rssi + 100)));
      const opt = document.createElement('option');
      opt.value = n.ssid;
      opt.textContent = n.ssid + ' (' + pct + '%' + (n.secure ? ' [SEC]' : '') + ')';
      sel.appendChild(opt);
    });
    result.textContent = nets.length ? (nets.length + ' networks found.') : 'No networks found.';
  }).catch(() => {
    if (attempt < 20) setTimeout(() => pollWifiScan(attempt + 1), 1000);
    else result.textContent = 'Scan failed.';
  });
}

function connectWifi() {
  const manual = document.getElementById('wifiManual').checked;
  const ssid = manual ? document.getElementById('wifiSsidManual').value.trim()
                      : document.getElementById('wifiSsid').value;
  const pass = document.getElementById('wifiPass').value;
  const result = document.getElementById('wifiResult');
  if (!ssid) { result.textContent = 'Please select or enter a network.'; return; }
  result.textContent = 'Connecting to ' + ssid + '… (can take ~15s)';
  const body = 'ssid=' + encodeURIComponent(ssid) + '&password=' + encodeURIComponent(pass);
  fetch('/api/wifi/connect', {
    method: 'POST',
    headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
    body: body
  }).then(r => r.json()).then(d => {
    if (d.success) {
      setTimeout(() => pollWifiConnect(0), 1500);
    } else {
      result.textContent = 'Failed: ' + (d.error || 'could not start connection') + '.';
    }
  }).catch(() => {
    setTimeout(() => pollWifiConnect(0), 1500);
  });
}

function pollWifiConnect(attempt) {
  const result = document.getElementById('wifiResult');
  fetch('/api/wifi/status').then(r => r.json()).then(d => {
    if (d.connected) {
      result.textContent = 'Connected! Reach the robot at ';
      appendRobotAddress(result, d);
      loadWifiStatus();
      return;
    }
    if (d.connecting) {
      if (attempt < 30) setTimeout(() => pollWifiConnect(attempt + 1), 1000);
      else result.textContent = 'Still trying… reopen Settings to check the status.';
      return;
    }
    result.textContent = 'Failed: ' + (d.lastError || 'could not connect') +
      '. Check the password and that it is a 2.4GHz network.';
  }).catch(() => {
    if (attempt < 30) setTimeout(() => pollWifiConnect(attempt + 1), 1000);
    else result.textContent = 'Lost contact with the robot. Rejoin its WiFi network and reopen Settings.';
  });
}

let activeGamepadIndex = null;
let gamepadPollId = null;
let lastButtonStates = [];
let lastAxisDir = { x: 0, y: 0 };
const axisThreshold = 0.5;
const pollIntervalMs = 80;

// Gamepad bindings adjusted to safe drone emotes
const buttonBindings = {
  0: () => pose('stand'),   // A / Cross
  1: () => enterDroneMode(),// B / Circle -> Drone Mode lock
  2: () => pose('crab'),    // X / Square
  3: () => pose('swim'),    // Y / Triangle
  4: () => pose('dead'),    // LB / L1
  5: () => pose('pushup'),  // RB / R1
  6: () => pose('bow'),     // LT / L2
  7: () => pose('shake'),   // RT / R2
  8: () => stop(),          // Back / Share
  9: () => pose('rest'),    // Start / Options
  10: () => pose('shake'),  // L3
  11: () => pose('bow'),    // R3
  12: () => move('forward'),// D-pad up
  13: () => move('backward'),// D-pad down
  14: () => move('left'),   // D-pad left
  15: () => move('right'),  // D-pad right
  16: () => stop(),         // Home / PS
  17: () => stop()          // Touchpad / extra
};

const buttonReleaseStop = new Set([12, 13, 14, 15]);

function updateGamepadStatus(connected) {
  const status = document.getElementById('gamepadStatus');
  if (!status) return;
  if (connected) {
    status.textContent = 'Gamepad connected';
    status.classList.add('connected');
  } else {
    status.textContent = 'Gamepad disconnected';
    status.classList.remove('connected');
  }
}

function handleButtonChange(index, pressed) {
  if (isDroneMode) return;
  if (pressed) {
    const action = buttonBindings[index];
    if (action) action();
  } else if (buttonReleaseStop.has(index)) {
    stop();
  }
}

function getAxisDirection(x, y) {
  if (Math.abs(x) < axisThreshold && Math.abs(y) < axisThreshold) return { x: 0, y: 0 };
  if (Math.abs(x) > Math.abs(y)) {
    return { x: x > 0 ? 1 : -1, y: 0 };
  }
  return { x: 0, y: y > 0 ? 1 : -1 };
}

function applyAxisDirection(dir) {
  if (isDroneMode) return;
  if (dir.x === 1) move('right');
  else if (dir.x === -1) move('left');
  else if (dir.y === 1) move('backward');
  else if (dir.y === -1) move('forward');
  else stop();
}

function pollGamepad() {
  if (isDroneMode) return;
  const pads = navigator.getGamepads ? navigator.getGamepads() : [];
  const pad = pads && activeGamepadIndex !== null ? pads[activeGamepadIndex] : null;
  if (!pad) {
    updateGamepadStatus(false);
    return;
  }
  updateGamepadStatus(true);

  if (!lastButtonStates.length) {
    lastButtonStates = pad.buttons.map(b => !!b.pressed);
  }
  pad.buttons.forEach((btn, i) => {
    const pressed = !!btn.pressed;
    if (pressed !== lastButtonStates[i]) {
      handleButtonChange(i, pressed);
      lastButtonStates[i] = pressed;
    }
  });

  const x = pad.axes[0] || 0;
  const y = pad.axes[1] || 0;
  const dir = getAxisDirection(x, y);
  if (dir.x !== lastAxisDir.x || dir.y !== lastAxisDir.y) {
    applyAxisDirection(dir);
    lastAxisDir = dir;
  }
}

window.addEventListener('gamepadconnected', (e) => {
  activeGamepadIndex = e.gamepad.index;
  lastButtonStates = [];
  lastAxisDir = { x: 0, y: 0 };
  updateGamepadStatus(true);
  if (!gamepadPollId) {
    gamepadPollId = setInterval(pollGamepad, pollIntervalMs);
  }
});

window.addEventListener('gamepaddisconnected', (e) => {
  if (activeGamepadIndex === e.gamepad.index) {
    activeGamepadIndex = null;
    lastButtonStates = [];
    lastAxisDir = { x: 0, y: 0 };
    updateGamepadStatus(false);
  }
});

if (navigator.getGamepads) {
  setInterval(() => {
    if (isDroneMode) return;
    if (activeGamepadIndex !== null) return;
    const pads = navigator.getGamepads();
    if (!pads) return;
    for (let i = 0; i < pads.length; i++) {
      if (pads[i]) {
        activeGamepadIndex = pads[i].index;
        updateGamepadStatus(true);
        if (!gamepadPollId) {
          gamepadPollId = setInterval(pollGamepad, pollIntervalMs);
        }
        break;
      }
    }
  }, 1000);
}
</script>
</body>
</html>
)rawliteral";
