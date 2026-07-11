#!/bin/bash

echo "[*] Building module..."
make || { echo "[-] Build failed."; exit 1; }

# Kill previous fake mousepad if exists
pkill -f "sleep 9999" 2>/dev/null

# Start a hidden-test process
sleep 9999 &
MOUSEPAD_PID=$!
echo "[*] Created fake 'mousepad' process (PID=$MOUSEPAD_PID)"

echo "[*] Removing previous module (if loaded)..."
sudo rmmod zk_rootkit 2>/dev/null || true

echo "[*] Inserting new module..."
sudo insmod zk_rootkit.ko || { echo "[-] Failed to insert module."; exit 1; }

echo "[*] Module status:"
lsmod | grep zk_rootkit

echo "[*] Recent kernel log:"
dmesg | grep ZK | tail -n 5
