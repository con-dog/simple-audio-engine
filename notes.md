Sample-rate: Number of times per second to sample the waveform
Bits-per-sample/Bit-depth: Number of bits per sample, basically how many possible values can be used to represent the amplitude of the wave at any sample point.

8-bit audio = 256 possible values, therefore center is 128 and range is 0 to 255

```latex
samples-per-cycle = sample-rate / frequency

eg  = 44100 / 440 = 100.22727272727273
```

```latex
wave(n) = center + amplitude * sin(theta)
```

We know that time-elapsed for a given sample number is given by sample number over sample rate

```latex
t(n) = n / sample-rate
```

And the number of cycles completed in that elapsed time for a given note frequency is given by:

```latex
no_cycles = note_frequency * t(n)
```

If we know 1 cycle is 2pi, then we can calculate theta for the angle at any given sample point n.

```latex
theta = no_cycles * 2 * PI
```

Now the full equation for the wave at any given sample point n is:

```latex
sample(n) = center + amplitude * sin((2 * PI * n * freq) /sample-rate)
```