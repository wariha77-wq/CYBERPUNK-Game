const http = require('http');
const fs = require('fs');
const path = require('path');
const pty = require('node-pty');

const PORT = 3000;
const EXE_PATH = path.join(__dirname, 'backend', 'CYBERPUNK.exe');
const FRONTEND_DIR = path.join(__dirname, 'frontend');

let ptyProcess = null;
let lastByteTime = 0;

// Exact structured data directly from GameData.inc & Mission01-05.inc
const MISSIONS = {
  1: {
    heading: 'MISSION 01: THE FIRST BREACH',
    intro: 'MISSION 01 INITIALIZED,',
    story: 'A security breach has been detected in the central network.',
    maxAttempts: 2,
    records: [
      {
        id: '01',
        name: 'RECORD 01:',
        badge: 'UNAUTHORIZED ACCESS',
        body: 'RECORD 01:\nTIME: 02:14\nLOCATION: SERVER ROOM\nSTATUS: UNAUTHORIZED ACCESS'
      },
      {
        id: '02',
        name: 'RECORD 02:',
        badge: 'ACCESS GRANTED',
        body: 'RECORD 02:\nTIME: 02:14\nLOCATION: DATA CORE\nSTATUS: ACCESS GRANTED'
      },
      {
        id: '03',
        name: 'RECORD 03:',
        badge: 'SYSTEM COMPROMISED',
        body: 'RECORD 03:\nTIME: 02:23\nLOCATION: SECURITY TERMINAL\nSTATUS: SYSTEM COMPROMISED'
      }
    ],
    question: 'WHO INITIATED THE BREACH?',
    options: [
      { value: 1, label: '1. SYSTEM ADMINISTRATOR' },
      { value: 2, label: '2. EXTERNAL INTRUDER' },
      { value: 3, label: '3. SECURITY AI' }
    ]
  },
  2: {
    heading: 'MISSION 02: THE DEADLOCK PROTOCOL',
    intro: 'MISSION 02: TRACE THE SIGNAL.',
    story: 'An unknown signal has infiltrated the network.',
    maxAttempts: 3,
    stages: {
      1: {
        name: 'STAGE 1: SIGNAL INTEGRITY',
        body: 'STAGE 1: SIGNAL INTEGRITY\nTHREE SIGNALS HAVE BEEN INTERCEPTED.\nTHE SYSTEM USES AN EVEN-NUMBERED SIGNAL PROTOCOL.\nVALID SIGNALS MUST END IN AN EVEN DIGIT.\nONLY ONE SIGNAL PASSES THE CHECK.\nIDENTIFY THE VALID SIGNAL.',
        question: 'WHICH SIGNAL PASSES THE INTEGRITY CHECK?',
        options: [
          { value: 1, label: '1. SIGNAL 731' },
          { value: 2, label: '2. SIGNAL 845' },
          { value: 3, label: '3. SIGNAL 862' },
          { value: 4, label: '4. SIGNAL 957' }
        ]
      },
      2: {
        name: 'STAGE 2: DATA RECONSTRUCTION',
        body: 'STAGE 2: DATA RECONSTRUCTION\nFRAGMENT A: 12 | FRAGMENT B: 24\nFRAGMENT C: 48 | FRAGMENT D: CORRUPTED',
        question: 'WHAT VALUE REPLACES THE CORRUPTED FRAGMENT?',
        options: [
          { value: 1, label: '1. 60' },
          { value: 2, label: '2. 72' },
          { value: 3, label: '3. 96' },
          { value: 4, label: '4. 108' }
        ]
      },
      3: {
        name: 'STAGE 3: SOURCE AUTHENTICATION',
        body: 'STAGE 3: SOURCE AUTHENTICATION\nORIGINAL SYSTEM RECORD:\nAUTHORIZATION CODE: 4821\nACCESS LOCATION: SERVER 04\nSTATUS: VERIFIED\n\nSOURCE A: CODE 4821 | LOCATION SERVER 04 | VERIFIED\nSOURCE B: CODE 4821 | LOCATION SERVER 09 | VERIFIED\nSOURCE C: CODE 7392 | LOCATION SERVER 04 | VERIFIED',
        question: 'WHICH SOURCE MATCHES THE ORIGINAL RECORD?',
        options: [
          { value: 1, label: '1. SOURCE A' },
          { value: 2, label: '2. SOURCE B' },
          { value: 3, label: '3. SOURCE C' }
        ]
      }
    }
  },
  3: {
    heading: 'MISSION 03: THE FALSE FACE',
    intro: 'MISSION 03: DEADLOCK PROTOCOL',
    story: 'FATAL ERROR: PROCESSOR EXECUTION BLOCKED. REGISTER CONFLICT DETECTED.',
    maxAttempts: 3,
    vectors: {
      1: {
        name: 'STAGE 01: REGISTER ARITHMETIC',
        body: 'ROUND 1: REGISTER ARITHMETIC\nMOV AX, 0015H\nMOV BX, 000AH\nADD AX, BX\nSUB AX, 0005H',
        question: 'Enter final AX value (decimal):'
      },
      2: {
        name: 'STAGE 02: HEXADECIMAL ARITHMETIC',
        body: 'ROUND 2: HEXADECIMAL ARITHMETIC\nMOV AL, 3AH\nADD AL, 0CH',
        question: 'Enter final AL value (decimal):'
      },
      3: {
        name: 'STAGE 03: MEMORY ADDRESSING',
        body: 'ROUND 3: MEMORY ADDRESSING\nMOV SI, 0004H\nMOV AX, [SI]\nMemory at offset 0004H contains 0012H.',
        question: 'Enter final AX value (decimal):'
      }
    }
  },
  4: {
    heading: 'MISSION 04: THE BROKEN PROTOCOL',
    intro: 'CENTRAL NETWORK FAILURE DETECTED.',
    story: 'OPERATOR 07: Restore the damaged system dependencies.',
    maxAttempts: 3,
    stages: {
      1: {
        title: 'SYSTEM STATUS',
        body: 'SYSTEM STATUS\nPOWER CORE: OFFLINE\nKERNEL: OFFLINE\nDRIVERS: OFFLINE\nDATABASE: OFFLINE\nNETWORK: OFFLINE',
        question: 'Q1: The Kernel requires power. What comes first?',
        options: [
          { value: 1, label: '1. DATABASE' },
          { value: 2, label: '2. POWER CORE' },
          { value: 3, label: '3. NETWORK' }
        ]
      },
      2: {
        title: 'BOOT SEQUENCE RECOVERY',
        body: 'BOOT SEQUENCE RECOVERY\nPOWER CORE: ONLINE\nKERNEL: INITIALIZED\nPENDING MODULES: DRIVERS / DATABASE / NETWORK',
        question: 'Q2: Kernel requires Power Core. What follows Kernel?',
        options: [
          { value: 1, label: '1. DATABASE' },
          { value: 2, label: '2. DRIVERS' },
          { value: 3, label: '3. NETWORK' }
        ]
      },
      3: {
        title: 'NETWORK RESTORATION',
        body: 'NETWORK RESTORATION\nDRIVERS: ONLINE\nDATABASE: RESTORED\nNETWORK: DISCONNECTED',
        question: 'Q3: Database is restored, but Network is disconnected.',
        options: [
          { value: 1, label: '1. Verify the network connection and restore communication.' },
          { value: 2, label: '2. Delete the database.' },
          { value: 3, label: '3. Shut down the Kernel.' }
        ]
      }
    }
  },
  5: {
    heading: 'MISSION 05: THE LAST PROTOCOL',
    intro: 'FINAL PROTOCOL ACTIVATED.',
    story: 'OPERATOR 07: The alien intelligence controls the central AI.',
    maxAttempts: 3,
    stages: {
      1: {
        title: 'FINAL CORE STATUS',
        body: 'FINAL CORE STATUS\nCORE STATUS: COMPROMISED\nHUMAN ACCESS: RESTRICTED\nBACKUP: AVAILABLE\nOVERRIDE: UNVERIFIED',
        question: 'Q1: The override command is unverified. What next?',
        options: [
          { value: 1, label: '1. Execute the override immediately.' },
          { value: 2, label: '2. Verify its authorization.' },
          { value: 3, label: '3. Delete the backup.' }
        ]
      },
      2: {
        title: 'CORE CONTAINMENT',
        body: 'CORE CONTAINMENT\nOVERRIDE AUTHORIZATION: REJECTED\nBACKUP INTEGRITY: VERIFIED\nMAIN CORE: COMPROMISED',
        question: 'Q2: Backup is verified, but the main core is compromised.',
        options: [
          { value: 1, label: '1. Restore the verified backup using approved recovery.' },
          { value: 2, label: '2. Trust the compromised core.' },
          { value: 3, label: '3. Delete all recovery data.' }
        ]
      },
      3: {
        title: 'SOVEREIGNTY RESTORATION',
        body: 'SOVEREIGNTY RESTORATION\nBACKUP RESTORATION: COMPLETE\nALIEN SUBROUTINE: CONTAINED\nAWAITING FINAL OPERATOR COMMAND',
        question: 'Q3: Choose the final action.',
        options: [
          { value: 1, label: '1. Preserve the alien intelligence.' },
          { value: 2, label: '2. Restore human control and isolate the compromised core.' },
          { value: 3, label: '3. Disable all human access permanently.' }
        ]
      }
    }
  }
};

function createEmptyState() {
  return {
    active: false,
    mission: 1,
    stage: 1,
    heading: MISSIONS[1].heading,
    intro: MISSIONS[1].intro,
    story: MISSIONS[1].story,
    records: MISSIONS[1].records,
    question: MISSIONS[1].question,
    options: MISSIONS[1].options,
    inputMode: 'OPTIONS',
    inputPrefix: '',
    score: 0,
    attempts: 2,
    maxAttempts: 2,
    status: 'PLAYING',
    lastFeedback: '',
    rawLog: ''
  };
}

let gameState = createEmptyState();

function sanitizeStream(raw) {
  return raw
    .replace(/\x1B\[\d+;\d+[Hf]/g, '\n')
    .replace(/\x1B\[\d*[ABCDEFGJK]/g, '\n')
    .replace(/\x1B\[[0-9;?]*[ -/]*[@-~]/g, '')
    .replace(/@@SYNC\|[^@\r\n]*@@/g, '\n')
    .replace(/\r/g, '\n')
    .replace(/[\x00-\x09\x0B-\x1F\x7F]/g, '')
    .replace(/(MISSION\s+0?[1-5]\s*:\s*THE\s+)/gi, '\n$1')
    .replace(/(STAGE\s+0?[1-6]\s*:)/gi, '\n$1')
    .replace(/(Q[1-3]\s*:)/gi, '\n$1');
}

function syncUiFromMissionAndStage(missionNum, stageNum) {
  const m = MISSIONS[missionNum] || MISSIONS[1];
  gameState.mission = missionNum;
  gameState.stage = stageNum;
  gameState.heading = m.heading;
  gameState.intro = m.intro;
  gameState.story = m.story;
  gameState.maxAttempts = m.maxAttempts;

  if (missionNum === 1) {
    gameState.inputMode = 'OPTIONS';
    gameState.inputPrefix = '';
    gameState.records = m.records;
    gameState.question = m.question;
    gameState.options = m.options;
  } else if (missionNum === 2) {
    gameState.inputMode = 'OPTIONS';
    gameState.inputPrefix = '';
    const stg = m.stages[stageNum] ? stageNum : 1;
    gameState.records = [1, 2, 3]
      .filter(n => n <= stg)
      .map(n => ({
        id: `S0${n}`,
        name: m.stages[n].name,
        badge: n === stg ? 'ACTIVE' : 'VERIFIED',
        body: m.stages[n].body
      }));
    gameState.question = m.stages[stg].question;
    gameState.options = m.stages[stg].options;
  } else if (missionNum === 3) {
    gameState.inputMode = 'TEXT';
    gameState.inputPrefix = 'DEC:';
    const vecNum = m.vectors[stageNum] ? stageNum : 1;
    gameState.records = [{
      id: `V0${vecNum}`,
      name: m.vectors[vecNum].name,
      badge: 'ACTIVE',
      body: m.vectors[vecNum].body
    }];
    gameState.question = m.vectors[vecNum].question;
    gameState.options = [];
  } else if (missionNum === 4 || missionNum === 5) {
    gameState.inputMode = 'OPTIONS';
    gameState.inputPrefix = '';
    const stg = m.stages[stageNum] ? stageNum : 1;
    gameState.records = [{
      id: 'SYS01',
      name: m.stages[stg].title,
      badge: 'LIVE STATUS',
      body: m.stages[stg].body
    }];
    gameState.question = m.stages[stg].question;
    gameState.options = m.stages[stg].options;
  }
}

function handleMasmChunk(rawChunk) {
  lastByteTime = Date.now();
  const clean = sanitizeStream(rawChunk);
  process.stdout.write(rawChunk);
  gameState.rawLog += clean;

  const lines = clean.split('\n').map(l => l.trim()).filter(Boolean);

  for (const line of lines) {
    // 1. Detect Mission Header
    const mMatch = line.match(/^MISSION\s+0?([1-5])\s*:\s*THE\s+/i);
    if (mMatch) {
      const nextMission = Number(mMatch[1]);
      gameState.attempts = nextMission === 1 ? 2 : 3;
      gameState.status = 'PLAYING';
      gameState.lastFeedback = '';
      syncUiFromMissionAndStage(nextMission, 1);
      continue;
    }

    // 2. Detect Stage Header ("STAGE 1: ..." / "STAGE 01: ...")
    const sMatch = line.match(/^STAGE\s+0?([1-6])\s*:/i);
    if (sMatch) {
      const nextStage = Number(sMatch[1]);
      syncUiFromMissionAndStage(gameState.mission, nextStage);
      continue;
    }

    // 2b. Direct Q1:/Q2:/Q3: fallback for Missions 04 & 05 (immune to ConPTY splitting "STAGE 02:")
    if (gameState.mission === 4 || gameState.mission === 5) {
      const qMatch = line.match(/^Q([1-3])\s*:/i);
      if (qMatch) {
        const qNum = Number(qMatch[1]);
        syncUiFromMissionAndStage(gameState.mission, qNum);
        continue;
      }
    }

    // 3. Attempts Remaining
    if (/Attempts remaining:/i.test(line)) {
      const am = line.match(/Attempts remaining:\s*(\d+)/i);
      if (am) gameState.attempts = Number(am[1]);
      continue;
    }

    // 4. Score Update
    if (/CURRENT PLAYER SCORE:/i.test(line)) {
      const sm = line.match(/CURRENT PLAYER SCORE:\s*(\d+)/i);
      if (sm) gameState.score = Number(sm[1]);
      continue;
    }

    // 5. Stage Complete
    if (/^STAGE\s+0?[1-3]\s+COMPLETE/i.test(line)) {
      gameState.lastFeedback = line;
      gameState.status = 'STAGE_CLEAR';
      continue;
    }

    // 6. Wrong Answer
    if (line.includes('INCORRECT') || line.includes('WRONG ANSWER!')) {
      gameState.lastFeedback = line;
      gameState.status = 'WRONG';
      continue;
    }

    // 7. Mission Complete
    if (
      line === 'MISSION COMPLETE.' ||
      line === 'MISSION 02 COMPLETE.' ||
      line.includes('DEADLOCK BROKEN!') ||
      line.includes('COMPLETED!')
    ) {
      gameState.lastFeedback = line;
      gameState.status = 'SUCCESS';
      continue;
    }

    // 8. Victory / Game Over
    if (line.includes('ALL FIVE MISSIONS COMPLETED') || line.includes('HUMANITY RESTORED')) {
      gameState.lastFeedback = line;
      gameState.status = 'VICTORY';
      continue;
    }
    if (line.includes('GAME OVER.') || line.includes('SYSTEM FAILURE')) {
      gameState.lastFeedback = line;
      gameState.status = 'GAMEOVER';
      continue;
    }
  }
}

function waitForPromptOrPause(offsetBefore, callback, maxWaitMs = 2000, expectedMission = null) {
  let finished = false;
  const done = () => {
    if (!finished) {
      finished = true;
      clearInterval(timer);
      clearTimeout(hardTimeout);
      callback(gameState);
    }
  };

  const timer = setInterval(() => {
    const fresh = gameState.rawLog.slice(offsetBefore);
    const hasPrompt =
      fresh.includes('ENTER YOUR ANSWER') ||
      fresh.includes('ENTER ANSWER') ||
      fresh.includes('Press any key to continue') ||
      gameState.status === 'GAMEOVER' ||
      gameState.status === 'VICTORY';

    const missionOk =
      expectedMission === null ||
      gameState.mission >= expectedMission ||
      gameState.status === 'VICTORY';

    if (hasPrompt && missionOk && Date.now() - lastByteTime >= 110) {
      done();
    }
  }, 25);

  const hardTimeout = setTimeout(done, maxWaitMs);
}

function startMasm(callback) {
  if (ptyProcess) {
    try { ptyProcess.kill(); } catch (_) {}
  }

  lastByteTime = Date.now();
  gameState = createEmptyState();
  gameState.active = true;

  if (!fs.existsSync(EXE_PATH)) {
    gameState.intro = `ERROR: Missing ${EXE_PATH}`;
    return callback(gameState);
  }

  ptyProcess = pty.spawn(EXE_PATH, [], {
    name: 'xterm-color',
    cols: 120,
    rows: 40,
    cwd: path.dirname(EXE_PATH),
    env: process.env
  });

  ptyProcess.onData(handleMasmChunk);
  waitForPromptOrPause(0, callback, 2000, 1);
}

const MIME_TYPES = {
  '.html': 'text/html',
  '.css': 'text/css',
  '.js': 'application/javascript',
  '.json': 'application/json',
  '.mp4': 'video/mp4',
  '.png': 'image/png',
  '.jpg': 'image/jpeg',
  '.svg': 'image/svg+xml'
};

const server = http.createServer((req, res) => {
  const urlPath = req.url.split('?')[0];

  if (req.method === 'POST' && urlPath === '/api/start') {
    startMasm((state) => {
      res.writeHead(200, { 'Content-Type': 'application/json' });
      res.end(JSON.stringify(state));
    });
    return;
  }

  if (req.method === 'GET' && urlPath === '/api/state') {
    if (ptyProcess && gameState.active) {
      res.writeHead(200, { 'Content-Type': 'application/json' });
      res.end(JSON.stringify(gameState));
    } else {
      startMasm((state) => {
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify(state));
      });
    }
    return;
  }

  if (req.method === 'POST' && urlPath === '/api/answer') {
    let body = '';
    req.on('data', chunk => { body += chunk; });
    req.on('end', () => {
      const { choice } = JSON.parse(body || '{}');
      gameState.status = 'PLAYING';
      const offsetBefore = gameState.rawLog.length;
      lastByteTime = Date.now();
      if (ptyProcess) ptyProcess.write(`${choice}\r`);
      waitForPromptOrPause(offsetBefore, (state) => {
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify(state));
      }, 1800);
    });
    return;
  }

  if (req.method === 'POST' && urlPath === '/api/continue') {
    const completedMission = gameState.mission;
    const nextExpectedMission = completedMission + 1;
    gameState.status = 'PLAYING';
    const offsetBefore = gameState.rawLog.length;
    lastByteTime = Date.now();
    if (ptyProcess) ptyProcess.write('\r');
    waitForPromptOrPause(offsetBefore, (state) => {
      // After Mission 05 completes, GameController enters VictoryScreen
      if (completedMission >= 5 && state.status !== 'GAMEOVER') {
        state.status = 'VICTORY';
        state.score = Math.max(state.score, 100);
      }
      res.writeHead(200, { 'Content-Type': 'application/json' });
      res.end(JSON.stringify(state));
    }, 2200, nextExpectedMission);
    return;
  }

  const safePath = urlPath === '/' ? '/main.html' : urlPath;
  const filePath = path.join(FRONTEND_DIR, safePath);
  const ext = path.extname(filePath).toLowerCase();

  fs.readFile(filePath, (err, content) => {
    if (err) {
      res.writeHead(404, { 'Content-Type': 'text/plain' });
      res.end('404 Not Found');
      return;
    }
    res.writeHead(200, { 'Content-Type': MIME_TYPES[ext] || 'application/octet-stream' });
    res.end(content);
  });
});

server.listen(PORT, () => {
  console.log(`CYBERPUNK 2086 // CONPTY MASM BRIDGE RUNNING at http://localhost:${PORT}`);
});