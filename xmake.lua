add_rules("mode.debug", "mode.release")
set_languages("c++17")

target("tree")
    add_rules("qt.widgetapp")
    add_headerfiles("src/*.h", "src/avl/*.h", "src/rbtree/*.h")
    add_files("src/*.cpp", "src/avl/*.cpp", "src/rbtree/*.cpp")
    add_files("src/mainwindow.ui")
    -- add files with Q_OBJECT meta (only for qt.moc)
    add_files("src/mainwindow.h")

target("ui")
    set_kind("phony")
    add_files("src/mainwindow.ui")
    add_files("src/avl/*.ui")
    add_files("src/rbtree/*.ui")
    on_load(function (target)
        for _, file in ipairs(target:sourcefiles()) do
            local idx = file:reverse():find("/", 1, true)
            local path, name
            if idx then
                path = file:sub(1, #file - idx + 1)
                name = file:sub(#file - idx + 2, #file - 3)
            else
                path = ""
                name = file
            end
            h_file = path .. "ui_" .. name .. ".h"
            os.vrun("uic -o " .. h_file .. " " .. file)
        end
    end)
