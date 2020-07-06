C++ does not the optional argumen initialization:
```c
int x = 2;
int y = tbs_enc_exp(x * x, thread_safe: false, re_encrypt: false);
```

So, we implement another "uglier" configuration interface:
```cpp
tbs_config cfg = TBS_CONFIG_DEFAULT;
cfg.thread_safe = false;
cfg.re_encrypt = false;
int x = 2;
int y = tbs_enc_exp_cfg(x * x, cfg)
```

Config by pointer is also ok (easier to update):
```cpp
tbs_config cfg = TBS_CONFIG_DEFAULT;
cfg.thread_safe = false;
cfg.re_encrypt = false;
int x = 2;
int y = tbs_enc_exp_cfgp(x * x, &cfg)
```
