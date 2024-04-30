idf_component_register(SRCS

  main.cpp

  # components
  modules/common/components/fl_widget.cpp
  modules/common/components/ui_utils.cpp

  # utils
  modules/common/utils/fl_async.cpp
  modules/common/utils/fl_async_hardware.cpp

  # app
  modules/app/widget.cpp
  modules/app/services/index.cpp

  # for test
  modules/tester/pack/index.cpp
  modules/tester/simple_page/index.cpp
  modules/tester/touch/index.cpp
)
