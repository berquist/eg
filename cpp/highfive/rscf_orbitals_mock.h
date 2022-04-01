#ifndef LIBGSCF_SCF_RSCF_ORBITALS_H
#define LIBGSCF_SCF_RSCF_ORBITALS_H

#include <cstddef>

namespace libgscf {

template<typename Tc, typename Te>
class rscf_orbitals {
public:
    size_t m_nbsf; //!< Number of basis function
    size_t m_nmo; //!< Number of MOs (linearly independent AOs)
    size_t m_nocc; //!< Number of occupied orbitals

    Tc m_c; //!< Molecular orbital coefficents
    Te m_eigval; //!< MO energies

    double m_objv; //!< Value of objective function

public:
    /** \brief Initializes the orbital container
     **/
    rscf_orbitals(size_t nbsf, size_t nmo, size_t nocc)
        : m_nbsf(nbsf), m_nmo(nmo), m_nocc(nocc)
        , m_c(-1), m_eigval(-1), m_objv(-1)
    { }
};


} // namespace libgscf

#endif // LIBGSCF_SCF_RSCF_ORBITALS_H
