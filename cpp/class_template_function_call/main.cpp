#include "class_template.h"
#include "consumer.h"

int main()
{

    const size_t dim = 2;
    const double f = 0.56;

    arma::vec fv3(dim);
    fv3.fill(f);

    foo::TestClass<arma::vec> tcv3(fv3);

    foo::consumer(&tcv3);

    return 0;

}
