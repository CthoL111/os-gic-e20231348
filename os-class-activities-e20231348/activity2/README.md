# Class Activity 2: Processes & IPC
**Student Name:** YAN CHANTHOL 
**Student ID:** e20231348 

## Task 1 Verification (Linux fork/exec)
* Parent PID: `1688362`
* Child PID: `1688363`
* Behavior Confirmation: The child process successfully slept for 30 seconds before replacing its image via `execlp` to run `ls -la`, which listed the directory structure back to the terminal. The parent caught the clean exit status 0.

## Task 2 Verification (Windows CreateProcess)
* Note: Task 2 is designed for a native Windows runtime configuration using the Win32 `CreateProcess` API to launch `mspaint.exe`. This component is saved within the `activity2/task2/winchild.c` tree layout ready for compilation on a native Windows workstation using MinGW/GCC.

## Task 3 Verification (Shared Memory IPC)
* Producer PID: `1688536`
* Consumer PID: `1688555`
* Execution Log:
  * Producer wrote: "Hello Pisey! Greetings from the Producer process."
  * Consumer read: "Hello Pisey! Greetings from the Producer process."
  * Action: Shared memory segment cleaned up successfully via `shm_unlink`.

## Task 4 Verification (Message Queue IPC)
* Sender PID: `1688651`
* Receiver PID: `1688661`
* Execution Log:
  * Sender dispatched message package to queue block.
  * Receiver successfully read: "Structured Message from Sender via POSIX Queue!"
  * Action: Resource successfully unlinked from operating system kernel via `mq_unlink`.
