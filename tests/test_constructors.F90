program test_constructors
    use autodiff
    use unittest

    implicit none

    real :: v, dg
    real, allocatable :: g(:), gg(:, :)
    type(GradRSP) :: go
    type(GradgradRSP) :: ggo
    type(DivgradRSP) :: dgo

    v = 1.0
    g = [2.0, 3.0]
    gg = reshape([4.0, 5.0, 5.0, 6.0], [2, 2])
    dg = 10.0

    go = GradRSP(v, g)
    call assert_equal(go%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(go%grad(), g, file=__FILE__, line=__LINE__)

    ggo = GradgradRSP(v, g, gg, .true.)
    call assert_equal(ggo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%divgrad(), dg, file=__FILE__, line=__LINE__)

    dgo = DivgradRSP(v, g, dg)
    call assert_equal(dgo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%divgrad(), dg, file=__FILE__, line=__LINE__)
end program test_constructors
