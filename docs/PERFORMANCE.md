# Performance Testing

Frame-rate stability is an active development area, including on MediaTek Helio G80. No FPS figures are claimed in this document until they have been measured and recorded.

## Record a test

For each run, record:

- Device model, chipset, RAM, and Android version
- App version or Git commit
- Internal/render resolution and graphics settings, if known
- Scene or mission and test duration
- Average FPS, 1% low (if available), and frame-time distribution
- CPU/GPU utilization and device temperature, if available
- Whether the device was thermally throttling

## Test scenes separately

1. Main menu / static scene
2. Quiet gameplay area
3. Combat with several enemies
4. Area with many effects or visible objects
5. Scene transition or loading
6. Longer session after the device has warmed up

Repeat each test under comparable conditions. Avoid comparing runs with different resolution, scene, thermal state, or background activity.

## Diagnose before optimizing

- CPU-bound: profile per-frame game/runtime work, recompilation overhead, synchronization, and avoidable allocations.
- GPU-bound: measure GPU load and investigate render resolution, shader cost, draw calls, and overdraw.
- Frame pacing: inspect frame times and synchronization; average FPS alone can hide stutter.
- Thermal throttling: compare short and sustained runs and note temperature changes.

Do not change several rendering systems at once. Keep a known-good build, change one factor at a time, and verify that visual correctness does not regress. These are diagnostic directions, not claims about the current bottleneck.
