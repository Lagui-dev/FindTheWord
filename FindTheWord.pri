!isEmpty(APP_PRI_INCLUDED):error("*.pri already included")

APP_PRI_INCLUDED = 1

APP_VERSION = 0.0.001
DISPLAY_VERSION = 0.0.001-beta
COPYRIGHT_YEAR = 2022

isEmpty(IDE_DISPLAY_NAME) : IDE_DISPLAY_NAME = FindTheWord
IDE_APP_TARGET  = "FindTheWord"
IDE_SOURCE_TREE = $$PWD

isEmpty(IDE_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    IDE_BUILD_TREE = $$clean_path($$OUT_PWD)
    IDE_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

#IDE_APP_PATH = $$IDE_BUILD_TREE/bin

CONFIG += c++14

defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    greaterThan(QT_MAJOR_VERSION, $$maj) {
        return(true)
    }
    return(false)
}
