Server Benchmarking
===================

## Description
This project aims to do server benchmarking for different kind of server implementations.<br>
Use apache `ab` to do load testing. Command: `ab -n 1000 -c <concurrency> -r http://server-ip:9876/`. And benchmarking result is showed with charts. For all kind of servers, `handle_request()` will `sleep` the working thread for 30 - 50 milliseconds to simulate a business server. And all server runs on `AWS EC2 Linux 3.14.35-28.38.amzn1.x86_64`, and set `net.core.somaxconn=1024`, and `listen(fd, backlog=1000)`. My NIC speed is `10000Mb/s`, `2.4GHz` CPU, `15G` RAM, `4` CPUs and `2` threads per core, and `2` cores per CPU. So I can start `4 * 2 * 2 = 16` threads to gain best performance if I use a thread pool and to decrease context switch of threads.

## Benchmarking Parameters
 - **millisecond per request:** time cost on every http request. mark as `0` if it exceeds 10 seconds.
 - **request per second:** http requests handled per second.
 - **concurrency step:** `1 10 20 40 60 80 100 200 400 600 800 1000`

## Blocking Server With Single Thread
**Blocing Server With Single Thread:** (request) => LOOP[(accpet connection) => (read request) => (handle request) => (response) => (close connection)], this routine is done in a single thread.<br>
**Name:** [blocking_server_v1](#)

## Blocking Server V2
**Blocking Server V2:** `fork` a child to handle every incoming requests, it's best performance seems to be **450 QPS, 600 concurrency**.<br>
**Name:** [blocking_server_v2](#)

## Blocking Server V3
**Blocking Server V3:** `fork` 15 children and one father to handle incoming requests, timeout happened after concurrency exceeds `60`, which marked as 0. There does not seem to have a thundering herd. I don't know why. So `Django` seems to be a very bad design.<br>
**Name:** [blocking_server_v3](#)

## Blocking Server V4
**Blocking Server V4:** `8` processes.<br>
**Name:** [blocking_server_v4](#)

## More Server Implements To Add
**To Be Continued ...**

## Benchmarking Charts
 - `x-axis` means concurrency.
 - millisecond per request: [https://live.amcharts.com/2NTc3/](https://live.amcharts.com/2NTc3/)
 - request per second: [https://live.amcharts.com/kYzM2/](https://live.amcharts.com/kYzM2/)<br><br>
<img src="https://github.com/linghuazaii/server-benchmark/blob/master/benchmarking/blocking_server_v2_time_per_request.png"></img><br>
<img src="https://github.com/linghuazaii/server-benchmark/blob/master/benchmarking/blocking_server_v2_request_per_second.png"></img><br>

## The End
Any suggestions, please add a `pull request` or send mail to [charlesliu.cn.bj@gmail.com](charlesliu.cn.bj@gmail.com) or [charlesliu.cn.bj@qq.com](charlesliu.cn.bj@qq.com).
