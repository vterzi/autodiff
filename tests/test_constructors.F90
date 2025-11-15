program test_constructors
    use autodiff
    use unittest

    implicit none

    integer :: i
    real :: v, dg
    real, allocatable :: g(:), gg(:, :), gg_(:, :)
    type(GradRSP) :: go
    type(GradgradRSP) :: ggo
    type(DivgradRSP) :: dgo

    v = 1.0
    g = [2.0, 3.0]
    gg = transpose(reshape([ &
        4.0, 5.0, &
        5.0, 6.0 &
    ], [2, 2]))
    dg = sum([(gg(i, i), i = 1, size(gg, 1))])

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

    gg_ = transpose(reshape([ &
        4.0, 5.0, &
        0.0, 6.0 &
    ], [2, 2]))
    ggo = GradgradRSP(v, g, gg_, .true.)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    gg_ = transpose(reshape([ &
        4.0, 0.0, &
        5.0, 6.0 &
    ], [2, 2]))
    ggo = GradgradRSP(v, g, gg_, .false.)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    gg_ = transpose(reshape([ &
        4.0, 5.0, &
        5.0, 6.0, &
        7.0, 8.0 &
    ], [2, 3]))
    ggo = GradgradRSP(v, g, gg_, .true.)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    gg_ = transpose(reshape([ &
        4.0, 5.0, 7.0, &
        5.0, 6.0, 8.0 &
    ], [3, 2]))
    ggo = GradgradRSP(v, g, gg_, .true.)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)

    gg = transpose(reshape([ &
        4.0, 5.0, &
        5.0, 0.0 &
    ], [2, 2]))

    gg_ = transpose(reshape([ &
        4.0, 5.0 &
    ], [2, 1]))
    ggo = GradgradRSP(v, g, gg_, .true.)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    gg_ = transpose(reshape([ &
        4.0, 5.0, 7.0 &
    ], [3, 1]))
    ggo = GradgradRSP(v, g, gg_, .true.)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    gg_ = transpose(reshape([ &
        4.0, &
        5.0 &
    ], [1, 2]))
    ggo = GradgradRSP(v, g, gg_, .false.)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    gg_ = transpose(reshape([ &
        4.0, &
        5.0, &
        7.0 &
    ], [1, 3]))
    ggo = GradgradRSP(v, g, gg_, .false.)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
end program test_constructors
