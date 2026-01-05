# PulseMux — Single-node Real-time Telemetry Processing Engine

## Overview

**PulseMux** is a single-node, real-time telemetry processing engine designed for Linux environments.  
It ingests high-throughput telemetry streams from IoT and edge systems, validates and normalizes events, performs windowed aggregations and anomaly detection, and emits results with predictable latency and bounded memory usage.

The project intentionally avoids distributed systems and external services, focusing instead on deterministic behavior, observability, and performance within a single long-running process.

---

## Problem Statement

In many production environments, telemetry data from sensors, trackers, gateways, or agents is written as raw events into files or queues. Aggregations and alerts are then computed by a monolithic offline or batch process running every few minutes.

This approach introduces several critical issues:

- delayed incident detection (minutes instead of seconds);
- bursty CPU and IO usage due to batch execution;
- lack of strict data contracts and validation guarantees;
- poor observability and difficult debugging;
- unbounded memory growth when input quality degrades;
- undefined behavior when encountering malformed or late events.

PulseMux replaces this architecture with a single Linux process that continuously processes telemetry streams in real time, providing low latency, predictable resource usage, and well-defined failure handling.

---

## End-to-End Behavior

PulseMux operates as a streaming processor with local state and explicit data quality control.

### Input Sources

- Standard input (`stdin`)
- Single input file
- Drop-folder directory with automatic detection of new files

### Processing Pipeline

Input
→ Parsing
→ Validation
→ Normalization
→ Deduplication
→ Routing
→ Windowed Aggregation
→ Anomaly Detection
→ Output

### Output Artifacts

- aggregated metrics per device or group in fixed time windows;
- alerts triggered by rule violations or anomalies;
- audit reports describing input quality issues;
- internal service metrics (throughput, latency, backpressure, memory).

The system starts with a single command, runs continuously for hours or days, tolerates malformed input according to policy, and shuts down gracefully with guaranteed buffer flushing.

---

## Key Features

- Multiple input modes: `stdin`, file, drop-folder
- Strict schema and business-rule validation
- Timestamp and unit normalization
- Event deduplication within a configurable time horizon
- Handling of out-of-order and late events
- Tumbling and sliding window aggregations
- Numeric aggregates: count, min, max, avg, p95
- Anomaly detection (thresholds, sudden changes, signal loss)
- Alert generation with deduplication and cooldown
- Structured logging and internal metrics
- Backpressure control and defined overflow behavior
- Graceful shutdown with clear state guarantees
- CLI for execution, config validation, dry-run, and benchmarks

---

## Data Format and Contracts

### Input Format

The input format is **NDJSON (JSON Lines)** encoded in UTF-8.  
Each line represents a single telemetry event.

### Mandatory Fields (`telemetry_event`)

- `event_id` — globally unique event identifier
- `ts` — event timestamp at the source (RFC3339)
- `ingest_ts` — event creation or emission time
- `tenant` — logical tenant or environment
- `device_id` — device identifier
- `metric` — metric name
- `value` — numeric value
- `seq` — monotonic per-device sequence number

### Optional Fields

- `tags` — arbitrary key-value attributes
- `quality` — event quality: `ok`, `suspect`, or `bad`

---

## Validation Errors

PulseMux classifies invalid input into the following categories:

- **Parse error** — invalid JSON syntax
- **Schema error** — missing mandatory fields or invalid types
- **Domain error** — values outside allowed ranges, unknown units, invalid timestamps
- **Policy error** — events violating configured time or routing policies

Invalid events never terminate the process unless explicitly configured to do so.

---

## Output Formats

- `aggregates.ndjson`
- `alerts.ndjson`
- `stats.ndjson`

---

## Concurrency Model

PulseMux is implemented as a multi-stage parallel pipeline:

- IO-bound input ingestion
- CPU-bound parsing and validation
- Stateful per-key aggregations
- Isolated IO-bound output writers

### Target Performance (8 CPU cores)

- ≥150,000 events/sec with rules disabled
- ≥60,000 events/sec with full feature set enabled
- p99 end-to-end latency ≤1500 ms

---

## Dependencies

- **C++20 / C++23**
- **simdjson** — SIMD-accelerated JSON parser for NDJSON ingestion

No other third-party runtime dependencies are used.

---

## Build

PulseMux uses **CMake** as its build system and targets Linux.

### Requirements

- Linux (x86_64)
- CMake ≥ 3.20
- GCC ≥ 11 or Clang ≥ 14
- simdjson (system package or submodule)

### Build Steps

```bash
git clone https://github.com/<your-username>/pulsemux.git
cd pulsemux

git submodule update --init --recursive

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -j
Run
From stdin
cat data/sample.ndjson | ./pulsemux

From file
./pulsemux --input data/sample.ndjson

Drop-folder mode
./pulsemux --input-dir data/inbox/
Design Notes

simdjson is used in streaming mode to minimize allocations and parsing latency

Parsing, validation, and normalization are strictly separated stages

Stateful components (deduplication, window aggregation) use bounded memory

Core data structures are designed for predictable latency and memory usage

Non-Functional Requirements

stable operation for at least 24 hours

RSS memory usage ≤800 MB

no memory leaks

correct handling of SIGINT and SIGTERM

full observability through logs and internal metrics

Failure Scenarios

Defined and tested scenarios include:

sudden input spikes

large volumes of malformed events

slow or failing output IO

out-of-order event bursts

shutdown under load

corrupted files in drop-folder mode

Project Scope

Allowed:

STL

simdjson

CMake-based build

Out of scope:

networking protocols

external databases

distributed processing

UI components

Repository Structure
project-root/
├─ apps/
├─ src/
├─ include/
├─ configs/
├─ data/
├─ tests/
├─ tools/
└─ docs/

Release Plan

MVP

single input source

NDJSON parsing

tumbling windows

aggregates output

logging and basic metrics

graceful shutdown

v1

drop-folder mode

event deduplication

out-of-order handling

p95 aggregation

alerting

backpressure control

full test suite

Acceptance Criteria

all functional scenarios work via CLI

performance targets are met

memory limits are respected

all tests and sanitizer runs pass

Out of Scope

networking integrations

external databases

Prometheus / OpenTelemetry SDKs

GUI

distributed processing
