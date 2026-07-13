# Measurement Methodology

Execution time was measured using the `clock()` function from `<time.h>`. Each benchmark was executed multiple times to reduce the impact of timing variability caused by background processes and operating system scheduling.

For the algorithm comparison experiment, both implementations were executed three times, and the average execution time was calculated.

# Observed Performance Differences

The naive implementation produced the following execution times:

- 2.769894 seconds
- 2.772130 seconds
- 2.760583 seconds

Average execution time:

2.767536 seconds

The single-pass implementation produced the following execution times:

- 0.000106 seconds
- 0.000107 seconds
- 0.000106 seconds

Average execution time:

0.000106333 seconds

Based on these measurements, the naive implementation was approximately 26,028 times slower than the single-pass implementation.

These results demonstrate that algorithmic complexity has a major impact on execution performance.

# Relation Between Runtime and Energy Consumption

Although power consumption was not directly measured, execution time can be used as an indirect indicator of computational efficiency.

The naive implementation kept the processor active for approximately 2.77 seconds, while the single-pass implementation completed its work almost instantly.

Because processors consume energy while executing instructions, reducing execution time generally reduces CPU activity time and may therefore decrease overall energy consumption.

For this reason, the single-pass implementation can be considered more energy efficient.

# Limitations of the Experiment

This experiment has several limitations.

First, actual electrical power consumption was not measured using hardware monitoring tools. Therefore, conclusions regarding energy efficiency are indirect.

Second, execution times may vary slightly because of background applications, cache effects, CPU frequency scaling, and operating system scheduling.

Finally, the `clock()` function measures processor time only and does not provide information about memory usage or real hardware power consumption.

# Practical Engineering Takeaway

This experiment demonstrates that choosing efficient algorithms can significantly improve both performance and potential energy efficiency.

By changing the algorithm design, execution time was reduced from approximately 2.77 seconds to 0.000106 seconds, representing an improvement of approximately 26 thousand times.

This shows that algorithmic optimization can provide far greater benefits than hardware improvements alone and should be considered an essential engineering practice in software development and green computing.
