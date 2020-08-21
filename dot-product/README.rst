Dot Product
-----------

.. highlight:: c

The dot product is an algebraic operation that takes two equal-length sequences
of numbers and returns a single number obtained by multiplying corresponding
entries and then summing those products. A common implementation of this
operation is shown below::

  double dot_product(int N, int v1[N], int v2[N]) {
    double result = 0.0;
    for (long i=0; i<N; i++)
      result += v1[i] * v2[i];

    return result;
  }

The example above is interesting from a programming model point of view because
it accumulates the result of each iteration on a single variable called
``result``. As we have already seen in this course, this kind of operation is
called reduction, and it is a very common pattern in scientific and
mathematical applications.

There are several ways to parallelize operations that compute a reduction:

 * Protect the reduction with a lock or atomic clause, so that only one thread
   increments the variable at the same time. Note that locks are expensive.
 * Specify that there is a dependency on the reduction variable, but choose
   carefully, you don't want to serialize the whole execution! In this exercise
   we are incrementing a variable, and the sum operation is commutative. OmpSs
   has a type of dependency called ''commutative'', designed specifically for
   this purpose.
 * Use a vector to store intermediate accumulations. Tasks operate on a given
   position of the vector (the parallelism will be determined by the vector
   length), and when all the tasks are completed, the contents of the vector
   are summed.


Once we have introduced the dot product operation and the different ways of
parallelizing a reduction, let's start this exercise. If you open the
*dot-product.c* file, you will see that the ``dot_product`` function is a bit
more complicated than the previous version.

.. Ternary operator is wrongly colored in C syntax. If newer versions ever fix it, c# can be removed.
.. code-block:: c#

    double result = 0.0;
    long j = 0;
    for (long i=0; i<N; i+=CHUNK_SIZE) {
        actual_size = (N - i >= CHUNK_SIZE) ? CHUNK_SIZE : N - CHUNK_SIZE;
        C[j] = 0;

        #pragma omp task label( dot_prod ) firstprivate( j, i, actual_size )
        {
            for (long ii=0; ii<actual_size; ii++)
                C[j] +=  A[i+ii] * B[i+ii];
        }

        #pragma omp task label( increment ) firstprivate( j )
        result += C[j];

        j++;
    }

Basically we have prepared our code to parallelize it, creating a private
storage for each chunk and splitting the main loop into two different nested
loops to adjust the granularity of our tasks (see ``CHUNK_SIZE`` variable).
Apart from that, we have also annotated the tasks for you, but this parallel
version is not ready, yet.
