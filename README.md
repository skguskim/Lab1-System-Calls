# 💻 운영체제 - Lab 1: xv6 System Calls

## 📖 프로젝트 소개


2026년 1학기 서울과학기술대학교 인공지능응용학과 **운영체제** 과목의 첫 번째 실습 과제 Lab 1: xv6: System Calls 입니다.
이 프로젝트는 xv6 운영체제 환경에서 **시스템 콜**을 활용하여 사용자 프로그램을 구현하고, OS 커널 내부를 직접 수정하여 새로운 시스템 콜을 추가하는 **커널 해킹** 과정을 수행하는 것을 목표로 합니다.

---

## ✨ 주요 내용

### 1. Hello, World
* "Hello, World!"를 출력하는 기본적인 사용자 프로그램 작성
* **구현 파일:** `user/hello.c` 

### 2. Unix command: cp
* 파일을 복사하는 UNIX `cp` 명령어의 단순화된 버전 구현
* `O_RDONLY`, `O_CREATE`, `O_WRONLY` 플래그와 `read`, `write` 시스템 콜을 사용하여 파일 데이터 복사
* **구현 파일:** `user/cp.c` [cite: 41]

### 3. RISC-V Privileged Mode & Internal
* **특권 명령어:** `ecall`(트랩 발생 및 서비스 요청), `sret`(Supervisor 모드 복귀), `mret`(Machine 모드 복귀)의 역할과 동작 방식 분석
* **부팅 단계별 모드:** `kernel/entry.S`(Machine), `kernel/start.c`(Machine), `kernel/main.c`(Supervisor)가 각각 어떤 모드에서 실행되는지 확인
* **제어 레지스터:** 트랩 처리에 사용되는 `stvec`(핸들러 주소), `sepc`(복귀 PC 값), `scause`(트랩 원인), `sstatus`(프로세서 상태) 레지스터의 역할 이해

### 4. Unix ps command 
* 현재 실행 중인 프로세스들의 상태 정보를 출력하는 `ps` 명령어 구현
* **커널 수정:** 22번 시스템 콜 번호(`SYS_ps`)를 정의하고, 커널 내부의 프로세스 테이블을 순회하며 정보를 수집하는 `print_ps` 함수 구현
* **데이터 보호:** 각 프로세스 정보에 접근할 때 데이터 꼬임 방지를 위해 `acquire(&p->lock)`와 `release(&p->lock)`를 사용하여 동기화 처리
* **출력 정보:** 프로세스 이름(`NAME`), 프로세스 ID(`PID`), 현재 상태(`STATE`)를 테이블 형식으로 출력

---

## 🖼️ 실행 결과

#### `cp` 명령어 실행 결과
* `cp` 명령어 사용 전에는 없던 `README2` 파일이 명령 실행 후에 생성된 것을 확인하여 정상 동작 검증 완료

#### `ps` 명령어 실행 결과
* 사용자 프로그램에서 `ps`를 입력하면 커널로부터 프로세스 정보를 받아 다음과 같이 출력

```text
NAME    PID     STATE
init    1       SLEEPING
sh      2       SLEEPING
ps      3       RUNNING
```

---

## ⚙️ 실행 환경 및 정보
*  **OS**: xv6-riscv (Windows 10 WSL)
* **Emulator**: QEMU 

---

## 📁 파일 구조 및 커널 수정 내역

실행 결과에 대한 상세한 분석 데이터와 커널 코드 수정 흐름은 함께 첨부된 **`report.pdf`** 보고서에서 확인하실 수 있습니다!

| 분류 | 파일 경로 | 주요 수정 사항 |
| :--- | :--- | :--- |
| **User Apps** | `user/hello.c`, `user/cp.c`, `user/ps.c` | 사용자 프로그램 로직 및 시스템 콜 호출 구현 |
| **System Call** | `kernel/syscall.h`, `kernel/syscall.c` | `SYS_ps` 정의(22번) 및 `sys_ps` 함수 매핑 추가 |
| **Kernel Logic** | `kernel/sysproc.c`, `kernel/proc.c` | `sys_ps` 래퍼 함수 및 실제 프로세스 상태를 출력하는 `print_ps` 로직 구현 |
| **Interface** | `user/user.h`, `user/usys.pl`, `kernel/defs.h` | 사용자 모드 시스템 콜 인터페이스 선언 및 커널 내부 선언 등록 |
| **Build** | `Makefile` | `UPROGS` 목록에 `_hello`, `_cp`, `_ps` 추가하여 컴파일 대상 등록 |

---
## 📜 저작권 (Copyright)
본 과제물의 모든 코드와 내용의 저작권은 원 출제자이신 **김한울 교수님**께 있습니다.

Copyright © 2026 Hanul Kim. All Rights Reserved.