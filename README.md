# CLI Log Analyzer for Linux services

## at the end of the project the program should:
    -Opens a log file
    -Reads it line by line
    -Parses each line
    -Filters lines by severity or time
    -Counts events
    -Prints a summary
    -Optionally writes filtered output to another file
    -Exits cleanly with proper error codes

## Required CLI arguments
    --file <path> (mandatory)
    --level <INFO|WARN|ERROR> (optional)
    --from <timestamp> (optional)
    --to <timestamp> (optional)
    --out <path> (optional)

### Output behavior
Always print:
    -Total lines processed
    -Lines matched
    -Count per log level
    -Number of malformed lines
    -Execution time
If --out is provided:
    -Write only matched lines to the file

    
    
    
last update i can open files reads them and Filters them what i want with --level
next step i need to handle --file files exestence. rejects unknown flags
