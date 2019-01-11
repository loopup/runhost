# runhost

&copy; 2019 LoopUp LLC. All rights reserved.

## Objective
Host for launching windows service for docker on windows server

<table>
<tr>
	<td>Project Location</td>
	<td>https://github.com/loopup/runhost</td>
</tr>
<tr>
	<td>Releases</td>
	<td>https://github.com/loopup/runhost/releases</td>
</tr>
</table>

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

### In `Dockerfile`

`ENTRYPOINT ["runhost.exe", "name of service"]`

> NOTE
>
> Windows Server Containers do not support interception of SIGTERM or SIGKILL as of this version.