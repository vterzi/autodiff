program test_operators
    use autodiff
    use unittest

    implicit none

    integer :: i
    real :: v1, v2, v, dg1, dg2, dg
    real, allocatable :: g1(:), g2(:), g(:), gg1(:, :), gg2(:, :), gg(:, :)
    type(GradRSP) :: go1, go2, go
    type(GradgradRSP) :: ggo1, ggo2, ggo
    type(DivgradRSP) :: dgo1, dgo2, dgo

    v1 = 1.0
    g1 = [2.0, 3.0]
    gg1 = transpose(reshape([ &
        4.0, 5.0, &
        5.0, 6.0 &
    ], [2, 2]))
    dg1 = sum([(gg1(i, i), i = 1, minval(shape(gg1)))])

    v2 = 1.0
    g2 = [4.0, 9.0]
    gg2 = transpose(reshape([ &
        16.0, 25.0, &
        25.0, 36.0 &
    ], [2, 2]))
    dg2 = sum([(gg2(i, i), i = 1, minval(shape(gg2)))])

    go1 = GradRSP(v1, g1)
    ggo1 = GradgradRSP(v1, g1, gg1, .true.)
    dgo1 = DivgradRSP(v1, g1, dg1)
    go2 = GradRSP(v1, g1)
    ggo2 = GradgradRSP(v1, g1, gg1, .true.)
    dgo2 = DivgradRSP(v1, g1, dg1)
    call assert_true(go1 == go2, file=__FILE__, line=__LINE__)
    call assert_true(ggo1 == ggo2, file=__FILE__, line=__LINE__)
    call assert_true(dgo1 == dgo2, file=__FILE__, line=__LINE__)
    go2 = GradRSP(v2, g2)
    ggo2 = GradgradRSP(v2, g2, gg2, .true.)
    dgo2 = DivgradRSP(v2, g2, dg2)
    call assert_true(go1 /= go2, file=__FILE__, line=__LINE__)
    call assert_true(ggo1 /= ggo2, file=__FILE__, line=__LINE__)
    call assert_true(dgo1 /= dgo2, file=__FILE__, line=__LINE__)

    go = +go1
    ggo = +ggo1
    dgo = +dgo1
    v = +v1
    g = +g1
    gg = +gg1
    dg = +dg1
    call assert_equal(go%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(go%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%divgrad(), dg, file=__FILE__, line=__LINE__)

    go = -go1
    ggo = -ggo1
    dgo = -dgo1
    v = -v1
    g = -g1
    gg = -gg1
    dg = -dg1
    call assert_equal(go%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(go%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%divgrad(), dg, file=__FILE__, line=__LINE__)

    go = go1 + go2
    ggo = ggo1 + ggo2
    dgo = dgo1 + dgo2
    v = v1 + v2
    g = g1 + g2
    gg = gg1 + gg2
    dg = dg1 + dg2
    call assert_equal(go%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(go%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%divgrad(), dg, file=__FILE__, line=__LINE__)

    go = go1 - go2
    ggo = ggo1 - ggo2
    dgo = dgo1 - dgo2
    v = v1 - v2
    g = g1 - g2
    gg = gg1 - gg2
    dg = dg1 - dg2
    call assert_equal(go%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(go%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%divgrad(), dg, file=__FILE__, line=__LINE__)

    go = go1 * go2
    ggo = ggo1 * ggo2
    dgo = dgo1 * dgo2
    v = v1 * v2
    g = g1 * v2 + v1 * g2
    gg = gg1 * v2 + v1 * gg2 + outer(g1, g2) + outer(g2, g1)
    dg = dg1 * v2 + v1 * dg2 + 2 * dot_product(g1, g2)
    call assert_equal(go%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(go%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%divgrad(), dg, file=__FILE__, line=__LINE__)

    go = go1 / go2
    ggo = ggo1 / ggo2
    dgo = dgo1 / dgo2
    v = v1 / v2
    g = (g1 * v2 - v1 * g2) / v2**2
    gg = ( &
        gg1 * v2 - v1 * gg2 &
        + 2 * v1 / v2 * outer(g2, g2) - outer(g1, g2) - outer(g2, g1) &
    ) / v2**2
    dg = ( &
        dg1 * v2 - v1 * dg2 &
        + 2 * v1 / v2 * dot_product(g2, g2) - 2 * dot_product(g1, g2) &
    ) / v2**2
    call assert_equal(go%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(go%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%divgrad(), dg, file=__FILE__, line=__LINE__)

    go = go1**go2
    ggo = ggo1**ggo2
    dgo = dgo1**dgo2
    v = v1**v2
    g = v1**v2 * (g1 * v2 / v1 + log(v1) * g2)
    gg = v1**v2 * ( &
        gg1 * v2 / v1 + log(v1) * gg2 &
        + (outer(g1, g2) + outer(g2, g1) - outer(g1, g1) * v2 / v1) / v1 &
        + outer(g1 * v2 / v1 + log(v1) * g2, g1 * v2 / v1 + log(v1) * g2) &
    )
    dg = v1**v2 * ( &
        dg1 * v2 / v1 + log(v1) * dg2 &
        + (2 * dot_product(g1, g2) - dot_product(g1, g1) * v2 / v1) / v1 &
        + dot_product( &
            g1 * v2 / v1 + log(v1) * g2, g1 * v2 / v1 + log(v1) * g2 &
        ) &
    )
    call assert_equal(go%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(go%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(ggo%gradgrad(), gg, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%val(), v, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%grad(), g, file=__FILE__, line=__LINE__)
    call assert_equal(dgo%divgrad(), dg, file=__FILE__, line=__LINE__)

contains
    pure function outer(vec1, vec2) result(mat)
        real, intent(in) :: vec1(:), vec2(:)
        real :: mat(size(vec1), size(vec2))

        integer :: i1, i2

        do i2 = 1, size(vec2)
            do i1 = 1, size(vec1)
                mat(i1, i2) = vec1(i1) * vec2(i2)
            end do
        end do
    end function outer
end program test_operators
