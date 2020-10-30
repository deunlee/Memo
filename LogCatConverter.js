// LogCat Converter

// input style : Logcat Reader
// output style : Zooo

const fs   = require('fs');
const path = require('path');


function main() {
    const args = process.argv.slice(2);
    switch (args.length) {
        case 0:
            const scriptName = path.basename(module.filename);
            console.log('>>> LogCatConverter.js');
            console.log('');
            console.log(`>>> Usage: node ${scriptName} <input-path>`);
            console.log(`>>> Usage: node ${scriptName} <input-path> <output-path>`);
            break;
    
        case 1:
            convert(args[0], args[0] + '_out.txt');
            break;

        case 2:
            convert(args[0], args[1]);
            break;
    
        default:
            console.log('Too many arguments!');
            break;
    }
}

function convert(inputPath, outputPath) {    
    // input
    if (!fs.existsSync(inputPath)) {
        console.log('Input file not exists.');
        return;
    }
    const rawLogs = fs.readFileSync(inputPath, 'utf8');
    const logs = rawLogs.split('\n\n');
    console.log(logs.length)
    // output
    const writer = fs.createWriteStream(outputPath, { flags: 'w' });
      
    // parse
    const reg = new RegExp('\[\d\d-\d\d \d\d:\d\d:\d\d.\d\d\d \d{2,}:\d{2,} [A-Z].*\]');
    // const logs = rawLogs.split('\n').slice(0,50).join('\n');
    // const reg = new RegExp('\[\d\d-\d\d \d\d:\d\d:\d\d.\d\d\d \d{2,}:\d{2,} [A-Z].*\]\n.*\n', 'g');
    // console.log(logs.match(reg));
    for (const log of logs) {
        const lines = log.split('\n');
        while (lines.length && !reg.test(lines[0])) {
            const trash = lines.shift();
            console.log('trash: ' + trash); // for debug
        }
        if (!lines.length) {
            continue;
        }
        const info = lines.shift().slice(1, -1).split(' ');
        const data = lines.join(' ');

        const date = info[0];
        const time = info[1];
        const pid  = info[2].split(':')[0];
        const tid  = info[2].split(':')[1];
        const type = info[3].substr(0, 1);
        const tag  = info[3].substr(2);

        const result = `${date} ${time} ${pid.padStart(5, ' ')} ${tid.padStart(5, ' ')} ${type} ${tag}: ${data}`;
        // console.log(result);
        writer.write(result + '\n');
    }

    writer.close();
    console.log('Finished!');
}



main();
