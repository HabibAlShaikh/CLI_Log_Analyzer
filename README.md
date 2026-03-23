# CLI Log Analyzer for Linux services
A CLI tool that parses and filters Linux log files.

## Build
```bash
g++ src/loganalyze.cpp -o loganalyze
```

## Usage
Usage:
```
loganalyze --path <path> [--level INFO|WARN|ERROR] [--out <path>]
```

## options
```--file```     Path to log file (required)
```--level```    Filter by log level
```--out```      Output file for matched lines
```--help```     Show this help message

## Examples
Input: ```./loganalyze --path /home/user/test.log```
Output:
2024-01-01 00:00:00 WARN line 0
...
Total lines: 100
Matched lines: 100

Input: ```./loganalyze --path /home/user/test.log --level ERROR```
Output:
2024-01-01 00:00:00 ERROR line 2
...
Total lines: 100
Matched lines: 34

Input: ```./loganalyze --path /home/user/test.log --level ERROR --out resalt.txt```
Output:
2024-01-01 00:00:00 ERROR line 2
...
Total lines: 100
Matched lines: 34
Output file: you will get file named resalt.txt

## Exit Code
0 = success
1 = error
