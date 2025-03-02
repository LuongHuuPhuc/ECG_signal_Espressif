set(req driver log esp_adc)
idf_component_register(SRCS "adc_config.c"
                      INCLUDE_DIRS "."
                      REQUIRES ${req})