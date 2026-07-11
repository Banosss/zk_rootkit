# ZK Rootkit for Kali Linux (Authorized Testing Use Only)

This module hides specified processes from system enumeration using DKOM.

## 💾 Requirements

- Kali Linux (Kernel version matching installed headers)
- Kernel headers (`sudo apt install linux-headers-$(uname -r)`)

## 🛠️ Build & Load

```bash
# Compile
make
```
<img width="709" height="125" alt="image" src="1.png" />
```bash
# Insert module (hides 'notepad' by default)
sudo insmod zk_rootkit.ko
```
<img width="335" height="56" alt="image" src="https://github.com/user-attachments/assets/5bb0e522-bc6c-4061-b2de-97e4eed9dc53" />
```bash
# Check status
lsmod | grep zk_rootkit
```
<img width="339" height="59" alt="image" src="https://github.com/user-attachments/assets/7624b83b-ab07-4f6b-8289-fcdc2ea9022d" />
```bash
# Remove when done
sudo rmmod zk_rootkit
```
<img width="332" height="45" alt="image" src="https://github.com/user-attachments/assets/fe076216-9747-4581-a4f4-e590a2cb1b0a" />

After the first time you running the whole process you could use the ./reload.sh to reboot the rootkit to get the result!
Good luck with your journey! hehe
```
<img width="702" height="311" alt="image" src="https://github.com/user-attachments/assets/a400f0d0-fd5e-4ca3-b858-f6ea24e6ede1" />
