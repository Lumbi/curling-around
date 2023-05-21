import 'react'
import { useState } from 'react'
import { Parameter } from './parameter'
import { Button, Input, Table, TableHead, TableRow, TableCell, TableBody, Typography, Stack, Box, InputAdornment, Icon } from '@mui/material'
import ErrorIcon from '@mui/icons-material/Error'

export const App = () => {
    const [parameters, setParameters] = useState<Parameter[]>([])

    const load = async (inputFile: File) => {
        const inputText = await inputFile?.text()
        const parameters = inputText
            .split('\n')
            .map(line => line.split('='))
            .map(([key, value]) => ({ key, value }))
        setParameters(parameters)
    }

    return (
        <>
            <Stack spacing={4}>
                <Stack direction='row' spacing={4}>
                    <Input
                        type='file'
                        color='primary'
                        onChange={async (event) => {
                            const input = event.target as HTMLInputElement
                            const inputFile = input.files?.item(0)
                            if (inputFile) {
                                load(inputFile)
                            }
                        }}
                    />
                    <Box display='flex' justifyContent='flex-end'>
                        <Button variant='contained'>Save</Button>
                    </Box>
                </Stack>
                <ParameterTable parameters={parameters}/>
            </Stack>
        </>
    )
}

const ParameterTable = (props: { parameters: Parameter[] }) => {
    return (
        <Table>
            <TableHead>
            </TableHead>
            <TableBody>
            {
                props.parameters.map(parameter => <ParameterRow key={parameter.key} parameter={parameter}/>)
            }
            </TableBody>
        </Table>
    )
}

const ParameterRow = (props: { parameter: Parameter }) => {
    const [parameterKey, setParameterKey] = useState(props.parameter.key)
    const [parameterValue, setParameterValue] = useState(props.parameter.value)

    const parameterValueIsInvalid = isNaN(Number(parameterValue)) || isNaN(parseFloat(parameterValue))

    return (
        <>
            <TableRow>
                <TableCell>
                    <Input
                        type='text'
                        value={parameterKey}
                        onChange={(event) => setParameterKey(event.target.value)}
                        fullWidth={true}
                    />
                </TableCell>
                <TableCell>
                    <Input
                        type='text'
                        value={parameterValue}
                        error={parameterValueIsInvalid}
                        endAdornment={
                            <InputAdornment position='end'>
                                {
                                    parameterValueIsInvalid
                                        ? <ErrorIcon color='error'/>
                                        : null
                                }
                            </InputAdornment>
                        }
                        onChange={(event) => setParameterValue(event.target.value)}
                        fullWidth={true}
                    />
                </TableCell>
            </TableRow>
        </>
    )
}
