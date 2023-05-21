export type Parameter = {
    key: string
    value: string
}

export function isValid(parameter: Parameter): boolean {
    return !isNaN(Number(parameter.value)) && !isNaN(parseFloat(parameter.value))
}
