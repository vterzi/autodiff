program kinds
    implicit none

    integer :: arg, prev_kind, curr_kind
    character(len=3) :: kind_label

    prev_kind = -1
    do arg = 0, 64
        curr_kind = selected_int_kind(arg)
        if (prev_kind >= 0 .and. curr_kind /= prev_kind) then
            select case (arg - 1)
            case (2)
                kind_label = 'K1'
            case (4)
                kind_label = 'K2'
            case (9)
                kind_label = 'K4'
            case (18)
                kind_label = 'K8'
            case (38)
                kind_label = 'K16'
            case default
                kind_label = '???'
            end select
            print *, kind_label // '=', prev_kind
        end if
        prev_kind = curr_kind
    end do

    prev_kind = -1
    do arg = 0, 64
        curr_kind = selected_real_kind(arg)
        if (prev_kind >= 0 .and. curr_kind /= prev_kind) then
            select case (arg - 1)
            case (3)
                kind_label = 'HP'
            case (6)
                kind_label = 'SP'
            case (15)
                kind_label = 'DP'
            case (18)
                kind_label = 'XDP'
            case (31, 33)
                kind_label = 'QP'
            case default
                kind_label = '???'
            end select
            print *, kind_label // '=', prev_kind
        end if
        prev_kind = curr_kind
    end do

    curr_kind = selected_char_kind('ASCII')
    if (curr_kind >= 0) print *, 'ASCII=', curr_kind
    curr_kind = selected_char_kind('ISO_10646')
    if (curr_kind >= 0) print *, 'UCS4=', curr_kind

    print *, 'LK=', kind(.false.)
    print *, 'IK=', kind(0)
    print *, 'RK=', kind(0.)
    print *, 'CK=', kind((0, 0))
    print *, 'SK=', kind('')
end program kinds
