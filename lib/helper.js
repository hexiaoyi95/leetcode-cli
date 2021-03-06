var fs = require('fs');
var path = require('path');

var _ = require('underscore');

var UNITS_SIZE = [
  {unit: 'B', name: 'Bytes',  count: 1024},
  {unit: 'K', name: 'KBytes', count: 1024},
  {unit: 'M', name: 'MBytes', count: 1024},
  {unit: 'G', name: 'GBytes', count: -1}
];

var UNITS_TIME = [
  {unit: 's', name: 'seconds', count: 60},
  {unit: 'm', name: 'minutes', count: 60},
  {unit: 'h', name: 'hours',   count: 24},
  {unit: 'd', name: 'days',    count: 7},
  {unit: 'w', name: 'weeks',   count: 4},
  {unit: 'm', name: 'months',  count: 12},
  {unit: 'y', name: 'years',   count: -1}
];

function getUnit(units, v) {
  for (var i = 0; i < units.length; ++i) {
    if (units[i].count <= 0 || v < units[i].count)
      return [v, units[i]];
    v /= units[i].count;
  }
}

var LANGS = [
  {lang: 'bash',       ext: '.sh',    style: '#'},
  {lang: 'c',          ext: '.c',     style: 'c'},
  {lang: 'cpp',        ext: '.cpp',   style: 'c'},
  {lang: 'csharp',     ext: '.cs',    style: 'c'},
  {lang: 'golang',     ext: '.go',    style: 'c'},
  {lang: 'java',       ext: '.java',  style: 'c'},
  {lang: 'javascript', ext: '.js',    style: 'c'},
  {lang: 'mysql',      ext: '.sql',   style: '#'},
  {lang: 'python',     ext: '.py',    style: '#'},
  {lang: 'python3',    ext: '.py3',   style: '#'},
  {lang: 'ruby',       ext: '.rb',    style: '#'},
  {lang: 'scala',      ext: '.scala', style: 'c'},
  {lang: 'swift',      ext: '.swift', style: 'c'}
];

var h = {};

h.prettyState = function(state) {
  switch (state) {
    case 'ac':    return this.prettyText('', true);
    case 'notac': return this.prettyText('', false);
    default:      return ' ';
  }
};

h.prettyText = function(text, yesNo) {
  var chalk = require('./chalk');
  var icon = require('./icon');
  switch (yesNo) {
    case true:  return chalk.green(icon.yes + text);
    case false: return chalk.red(icon.no + text);
    default:    return text;
  }
};

h.prettySize = function(n) {
  var res = getUnit(UNITS_SIZE, n);
  return res[0].toFixed(2) + res[1].unit;
};

h.prettyTime = function(n) {
  var res = getUnit(UNITS_TIME, n);
  return res[0].toFixed(0) + ' ' + res[1].name;
};

h.levelToName = function(level) {
  switch (level) {
    case 1:  return 'Easy';
    case 2:  return 'Medium';
    case 3:  return 'Hard';
    default: return ' ';
  }
};

h.statusToName = function(sc) {
  switch (sc) {
    case 10: return 'Accepted';
    case 11: return 'Wrong Answer';
    case 12: return 'Memory Limit Exceeded';
    case 13: return 'Output Limit Exceeded';
    case 14: return 'Time Limit Exceeded';
    case 15: return 'Runtime Error';
    case 16: return 'Internal Error';
    case 20: return 'Compile Error';
    case 21: return 'Unknown Error';
    default: return 'Unknown';
  }
};

h.langToExt = function(lang) {
  var res = _.find(LANGS, function(x) {
    return x.lang === lang;
  });
  return res ? res.ext : '.raw';
};

h.extToLang = function(fullpath) {
  var ext = path.extname(fullpath);
  var res = _.find(LANGS, function(x) {
    return x.ext === ext;
  });
  return res ? res.lang : 'unknown';
};

h.langToCommentStyle = function(lang) {
  var res = _.find(LANGS, function(x) {
    return x.lang === lang;
  });

  return (res && res.style === '#') ?
  {commentHeader: '#',  commentLine: '#',  commentFooter: '#'} :
  {commentHeader: '/*', commentLine: ' *', commentFooter: ' */'};
};

h.getFileData = function(p) {
  return fs.existsSync(p) ? fs.readFileSync(p).toString() : null;
};

h.getDirData = function(p) {
  var dir = path.join(__dirname, '..', p);
  return _.map(fs.readdirSync(dir), function(f) {
    return {
      name: path.basename(f, '.json'),
      data: JSON.parse(fs.readFileSync(path.join(dir, f)))
    };
  });
};

h.getFilename = function(fullpath) {
  return path.basename(fullpath, path.extname(fullpath));
};

h.getHomeDir = function() {
  return process.env.HOME || process.env.USERPROFILE;
};

h.getCacheDir = function() {
  return path.join(this.getHomeDir(), '.lc');
};

h.getCacheFile = function(k) {
  return path.join(this.getCacheDir(), k + '.json');
};

h.getConfigFile = function() {
  return path.join(this.getHomeDir(), '.lcconfig');
};

h.readStdin = function(cb) {
  var stdin = process.stdin;
  var bufs = [];

  stdin.on('readable', function() {
    var data = stdin.read();
    if (data) bufs.push(data);
  });
  stdin.on('end', function() {
    cb(null, Buffer.concat(bufs).toString());
  });
  stdin.on('error', cb);
};

h.getSetCookieValue = function(resp, key) {
  var cookies = resp.headers['set-cookie'];
  if (!cookies) return null;

  for (var i = 0; i < cookies.length; ++i) {
    var sections = cookies[i].split(';');
    for (var j = 0; j < sections.length; ++j) {
      var kv = sections[j].trim().split('=');
      if (kv[0] === key) return kv[1];
    }
  }
  return null;
};

h.printSafeHTTP = function(msg) {
  return msg.replace(/(Cookie\s*:\s*)'.*?'/, '$1<hidden>')
    .replace(/('X-CSRFToken'\s*:\s*)'.*?'/, '$1<hidden>')
    .replace(/('set-cookie'\s*:\s*)\[.*?\]/, '$1<hidden>');
};

module.exports = h;
