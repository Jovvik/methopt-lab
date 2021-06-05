[![Actions Status](https://github.com/Jovvik/methopt-lab/workflows/Windows/badge.svg)](https://github.com/Jovvik/methopt-lab/actions)
[![Actions Status](https://github.com/Jovvik/methopt-lab/workflows/Ubuntu/badge.svg)](https://github.com/Jovvik/methopt-lab/actions)
[![Actions Status](https://github.com/Jovvik/methopt-lab/workflows/Standalone/badge.svg)](https://github.com/Jovvik/methopt-lab/actions)
[![codecov](https://codecov.io/gh/Jovvik/methopt-lab/branch/master/graph/badge.svg?token=MY41M3TGE2)](https://codecov.io/gh/Jovvik/methopt-lab)

# Лабораторные по методами оптимизации команды ∀ 𝘙̅ ∈ ℛⁿ: 𝐑(𝘙̅) ∈ ℛ (КаМаЗ)

## Как билдить

### Из консоли

`cmake -Hall -Bbuild`

`cmake --build build`

### IDE

Необходимо указать, что основной `CmakeLists.txt` лежит в папке `all`.

## Как запускать/тестить

Надо все запускать из корня проекта. Для clion это настраивается в "Edit configurations..." -> "Working directory"
