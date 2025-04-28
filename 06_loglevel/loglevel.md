### 内核日志
内核日志

printk（​​print kernel​​）是内核中最底层的日志输出函数，用于向内核日志缓冲区（dmesg）或控制台打印消息。
支持指定​​日志级别​​（如 KERN_INFO、KERN_ERR 等），通过优先级控制消息的输出位置(如是否显示到控制台);
如：`printk(KERN_INFO "Message: %s\n", arg);`
同时，pr_ 系列宏（如 pr_info、pr_err）是对 printk 的封装，提供更简洁的语法。
自动添加日志级别，并支持统一的格式化前缀（如模块名、函数名、行号等）。如:
```c
#define pr_fmt(fmt) "MyModule: " fmt
pr_info("Message: %s\n", arg);  // 输出：MyModule: Message: arg
```
| 宏                     | 对应的日志级别       | 说明                              |
|------------------------|---------------------|-----------------------------------|
| `pr_emerg(fmt, ...)`   | `KERN_EMERG`        | 系统不可用（最高优先级）             |
| `pr_alert(fmt, ...)`   | `KERN_ALERT`        | 需要立即处理的问题                  |
| `pr_crit(fmt, ...)`    | `KERN_CRIT`         | 严重错误（如硬件故障）               |
| `pr_err(fmt, ...)`     | `KERN_ERR`          | 一般错误                           |
| `pr_warn(fmt, ...)`    | `KERN_WARNING`      | 警告（潜在问题）                    |
| `pr_notice(fmt, ...)`  | `KERN_NOTICE`       | 正常但重要的事件                    |
| `pr_info(fmt, ...)`    | `KERN_INFO`         | 一般信息                           |
| `pr_debug(fmt, ...)`   | `KERN_DEBUG`        | 调试信息（需启用 `DEBUG` 宏）        |

#### 使用内核日志
内核日志的优先级由低到高分为 8 个级别（0=EMERG 到 7=DEBUG），可通过 dmesg 的 -l 参数筛选：
# 仅显示错误（ERR）及以上级别的高优先级日志
dmesg -l err,crit,alert,emerg

# 显示警告（WARNING）和信息（INFO）级别日志
dmesg -l warn,info