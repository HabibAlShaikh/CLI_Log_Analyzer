# CLI Log Analyzer for Linux services
A CLI tool that parses and filters Linux log files.

## Build
```bash
g++ src/loganalyze.cpp -o loganalyze
```

## Usage
Usage:
```
loganalyze --file <path> [--level INFO|WARN|ERROR|DEBUG] [--from ""YYYY-MM-DD HH:MM:SS""] [--to ""YYYY-MM-DD HH:MM:SS""] [--out <path>]
```

## options
```--path```     Path to log file (required)  
```--level```    Filter by log level  
```--out```      Output file for matched lines  
```--from```     Start timestamp (inclusive)  
```--to```       End timestamp (inclusive)  
```--help```     Show this help message

## Examples
Input: ```./loganalyze --path /home/user/test.log```  
Output:
```
2024-01-01 00:00:00 WARN line 0
...
Total lines: 100
Matched lines: 100
```

Input: ```./loganalyze --path /home/user/test.log --level ERROR```  
Output:
```
2024-01-01 00:00:00 ERROR line 2
...
Total lines: 100
Matched lines: 34
```

Input: ```./loganalyze --path /home/user/test.log --level ERROR --out resalt.txt```  
Output:
```
2024-01-01 00:00:00 ERROR line 2
...
Total lines: 100
Matched lines: 34
```  
Output file: you will get file named resalt.txt


Input: ```./loganalyze --path /var/log/archinstall/install.log --from "2026-02-07 07:46:00" --to "2026-02-07 07:49:09"```  
Output:
```
[2026-02-07 07:46:08] - DEBUG - Hardware model detected: Gigabyte Technology Co., Ltd. B550M AORUS PRO-P; UEFI mode: True
...
[2026-02-07 07:48:58] - DEBUG - Creating yescrypt hash with rounds 5
Total lines: 1238
Matched lines: 17
```

## Exit Code
0 = success  
1 = error
