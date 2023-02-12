# NanoLog
C++20 Nano logging library

# NanoLog is not the fastest nor the most convenient

# Examples

```cpp
    // print some message with different error level
    NNL_LOGI(std::cout, "message with one arg: \"{}\"\n", "arg0");
    NNL_LOGD(std::cout, "message with one arg: \"{}\"\n", "arg0");
    NNL_LOGW(std::cout, "message with one arg: \"{}\"\n", "arg0");
    NNL_LOGE(std::cout, "message with one arg: \"{}\"\n", "arg0");
    // the fully qualified macros can also be used:
    // NNL_LOG_INFO, NNL_LOG_DEBUG, NNL_LOG_WARNING, NNL_LOG_ERROR

    // conditional print some message with different error level
    NNL_LOGI_IF(true, std::cout, "message with one arg: \"{}\"\n", "arg0");
    NNL_LOGD_IF(true, std::cout, "message with one arg: \"{}\"\n", "arg0");
    NNL_LOGW_IF(true, std::cout, "message with one arg: \"{}\"\n", "arg0");
    NNL_LOGE_IF(true, std::cout, "message with one arg: \"{}\"\n", "arg0");
    // the fully qualified macros can also be used:
    // NNL_LOG_INFO_IF, NNL_LOG_DEBUG_IF, NNL_LOG_WARNING_IF, NNL_LOG_ERROR_IF

    // try-catch wrapper with logging
    std::string str;
    NNL_TRY_CATCH(std::cout, str = "some string";);

    // try-catch-rethrow wrapper with logging
    std::string str2;
    NNL_TRY_CATCH_RETHROW(std::cout, str2 = "another string";);

    // try-catch-abort wrapper with logging
    std::string str3;
    NNL_TRY_CATCH_ABORT(std::cout, str3 = "different string";);

    // FILE-IO for logging
    // open log-file (always in append mode if they exists)
    NNL_CREATE_LOG_STREAM(
         logfile // var name
        ,"logfile.log" // file name
    );
    // logging to file
    NNL_LOGI(logfile, "message with one arg: \"{}\"\n", "arg0");
    // close log-file
    NNL_CLOSE_LOG_STREAM(logfile);
```
# Output example
```
/home/nixman/projects/nanolog/test.cpp(  49)[2023.02.12-12:04:51.240][I]: message with one arg: "arg0"
/home/nixman/projects/nanolog/test.cpp(  50)[2023.02.12-12:04:51.240][D]: message with one arg: "arg0"
/home/nixman/projects/nanolog/test.cpp(  51)[2023.02.12-12:04:51.240][W]: message with one arg: "arg0"
/home/nixman/projects/nanolog/test.cpp(  52)[2023.02.12-12:04:51.240][E]: message with one arg: "arg0"
```

# Useful macro
 - `NNL_USE_STDIO` - to work with FILE streams like `stdout`/`stderr`.
 - `NNL_DONT_SHOW_DATETIME` - omit date-time in messages.
 - `NNL_CONSIDER_TIMEZONE` - take into account the time-zone instead of using UTC+0.
 - `NNL_SHORT_FILEPATH` - show file-name only instead of full file-path.
 - `NNL_DISABLE_LOGGING` - disable any logging functionality without any code changes.
 - `NNL_FLUSH_EACH_RECORD` - forcibly flush each message to used IO-stream.
