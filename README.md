# runhost
Host for launching windows service for docker on windows server

## Usage

`runhost.exe "name of service"`

```
Attempting to start `name of service`..
Waiting for signal (or hit `q` to quit)..
```

- There is no check for service name validity.
- There is no check for service startup status.
- There is no error checking or recovery.
- The purpose is to allow for handling/intercept of `SIGINT`, `SIGTERM`, `SIGKILL` signals and return code accordingly.
