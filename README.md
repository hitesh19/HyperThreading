# HyperThreading
Here we will try to explain what is HyperThreading and its Performance

What is HyperThreading?

With Hyper-Threading, a microprocessor's "core" processor can execute two (rather than one) concurrent streams (or threads) of instructions sent by the operating system. Having two streams of execution units to work on allows more work to be done by the processor during each clock cycle. 
To the operating system, the Hyper-Threading microprocessor appears to be two separate processors. Because most of today's operating systems (such as Windows and Linux) are capable of dividing their workload among multiple processors (this is called symmetric multiprocessing or SMP ), the operating system simply acts as though the Hyper-Threading processor is a pool of two processors.

HyperThreading Performance -

Hyperthreading performance depends on many factors and is difficult to estimate.

So you only really get additional performance out of hyperthreads if the two threads running on the same core use different execution units and each thread on it's own would have too many adata dependencies. For example one thread only does integer ops, the other one only floating point. Then you can see extra performance because you are using more execution units per cycle.

But this in turn depends on how your OS schedules threads onto hyperthreads. From the point of view of the OS each hyperthread is a logical CPU. So it's entirely up to the scheduler what to put there and when.

In practice hyperthreads will give you at most 10-20% extra performance. On our HPC we have turned them off (for licensing reasons mainly though).

You cannot  deploy code onto hyperthreads directly yourself. The OS will do that for you. You can set scheduling affinities for your user land threads, but it is still all up to the scheduler to actually deploy your threads. This is done transparently to the programmer. A good scheduler will deploy your code evenly first on cores and only resort to hyperthreads if all cores are busy.
(src: https://stackoverflow.com/questions/18831996/hyperthreading-code-example)

Here are the stats for 4 core 8 thread Benchmarks by Roy Longbottom -
(src: http://www.roylongbottom.org.uk/quad%20core%208%20thread.htm)

To test whether hyperThread is enabled on your system please run the attach .sln on your visual studio or you can use the help of the following link to check the same -
https://stromasys.atlassian.net/wiki/spaces/KBP/pages/47350211/How+to+check+if+hyper-threading+is+enabled+in+Windows


If its not enabled then you can enable it from the BIOS.
