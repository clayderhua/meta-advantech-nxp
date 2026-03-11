set_modules_enable_or_not() {

    local func_list="$1"
    local json_file="$2"
    local target_conf="$3"

    echo "Clear function flags first !!"
    for feature in $func_list; do
        eval "enable_${feature}=0"
    done

    for feature in $func_list; do

        local enabled_val=$(jq -r --arg group "$target_conf" --arg func "$feature" '.[$group][$func].enabled' $json_file)

        if [ "$enabled_val" = "1" ]; then
            eval "enable_${feature}=1"
            echo "$feature function enabled"
        fi

        dependencies=$(jq -r --arg group "$target_conf" --arg func "$feature" '
            if .[$group][$func].dependencies then
                .[$group][$func].dependencies[]
            else
                empty
            end
        ' $json_file)

        for dependency in $dependencies; do
            if echo "$func_list" | grep -q -w "$dependency"; then
                eval "enable_${dependency}=1"
                echo "$feature dependent with $dependency"
            fi
        done

    done
}

get_namelist_of_conf_root() {
    local json_file="$1"
    jq -r 'keys[]' ${json_file}
}
