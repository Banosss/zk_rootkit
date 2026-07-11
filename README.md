# ZK Rootkit for Kali Linux (Authorized Testing Use Only)

This module hides specified processes from system enumeration using DKOM.

## 💾 Requirements

- Kali Linux (Kernel version matching installed headers)
- Kernel headers (`sudo apt install linux-headers-$(uname -r)`)

## 🛠️ Build & Load

```bash
# Compile
make

# Insert module (hides 'notepad' by default)
sudo insmod zk_rootkit.ko

# Check status
lsmod | grep zk_rootkit

# Remove when done
sudo rmmod zk_rootkit
